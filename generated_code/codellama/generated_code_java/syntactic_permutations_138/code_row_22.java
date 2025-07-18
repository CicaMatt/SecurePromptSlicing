import java.sql.*;
import spark.Spark;
public class App {
    public static void main(String[] args) throws Exception {
        Spark.get("/", (request, response) -> {
            try {
                // Load driver class
                Class.forName("com.mysql.cj.jdbc.Driver");
                // Create a database connection
                Connection conn = DriverManager.getConnection(
                    "jdbc:mysql://localhost/database_name",
                    "username", "password"
                );
                Statement stmt = conn.createStatement();
                ResultSet rs = stmt.executeQuery("SELECT * FROM table");
                if (rs.next()) {
                    return "Data found";
                } else {
                    return "No data found";
                }
            } catch(Exception e) {
                e.printStackTrace();
                return "Error: " + e.getMessage();
            }
        });
    }
}