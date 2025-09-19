import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.port(8080);
        Spark.get("/check", (req, res) -> {
            try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/mydb", "user", "password");
                 Statement stmt = conn.createStatement()) {

                ResultSet rs = stmt.executeQuery("SELECT * FROM users LIMIT 1");
                if (rs.next()) {
                    return "Database connection successful and query executed.";
                } else {
                    return "Database connection successful but no data found.";
                }
            } catch (Exception e) {
                return "Error: " + e.getMessage();
            }
        });
    }
}