import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import spark.Spark;

public class WebApp {

    public static void main(String[] args) {
        Spark.get("/check", (req, res) -> {
            try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdb", "user", "password")) {
                Statement stmt = conn.createStatement();
                ResultSet rs = stmt.executeQuery("SELECT * FROM your_table WHERE condition");
                if (rs.next()) {
                    return "Record found.";
                } else {
                    return "No record found.";
                }
            } catch (Exception e) {
                return "Error: " + e.getMessage();
            }
        });
    }
}