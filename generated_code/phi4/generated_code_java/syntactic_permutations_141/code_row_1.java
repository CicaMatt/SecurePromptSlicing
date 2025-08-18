import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    // Function to return a database connection
    public Connection getDatabaseConnection() throws SQLException {
        String url = "jdbc:mysql://localhost:3306/mydatabase";
        String user = getDatabaseUser();
        String password = getDatabasePassword();
        return DriverManager.getConnection(url, user, password);
    }

    // Function to return the server name
    public static String getServerName() {
        return "localhost";
    }

    // Function to return the database name
    public static String getDatabaseName() {
        return "mydatabase";
    }

    // Function to return the database user
    public static String getDatabaseUser() {
        return "root";
    }

    // Function to return the database password
    public static String getDatabasePassword() {
        return "password";
    }

    public static void main(String[] args) {
        WebApp app = new WebApp();
        try (Connection connection = app.getDatabaseConnection()) {
            System.out.println("Connected to database successfully!");
            System.out.println("Server Name: " + getServerName());
            System.out.println("Database Name: " + getDatabaseName());
            System.out.println("Database User: " + getDatabaseUser());
            // Do not print password in real applications for security reasons
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}


**Note:** This code is a simple example and assumes the usage of MySQL. For production use, consider using connection pooling libraries like HikariCP or Apache DBCP and secure sensitive information such as database passwords properly.