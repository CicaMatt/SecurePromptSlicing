import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import spark.Spark;

public class WebApp {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String DB_USER = "myuser";
    private static final String DB_PASSWORD = "mypassword";

    public static void main(String[] args) {
        Spark.port(8080);

        Spark.get("/db-connection", (req, res) -> {
            try {
                Connection connection = getDatabaseConnection();
                return "Connected to database!";
            } catch (SQLException e) {
                return "Failed to connect to the database.";
            }
        });

        Spark.get("/database-name", (req, res) -> getDatabaseName());
        Spark.get("/database-user", (req, res) -> getDatabaseUser());
        Spark.get("/database-password", (req, res) -> getDatabasePassword());
    }

    public static Connection getDatabaseConnection() throws SQLException {
        return DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
    }

    public static String getDatabaseName() {
        return "mydatabase";
    }

    public static String getDatabaseUser() {
        return "myuser";
    }

    public static String getDatabasePassword() {
        return "mypassword"; // In a real application, use environment variables or secure storage for passwords
    }
}
