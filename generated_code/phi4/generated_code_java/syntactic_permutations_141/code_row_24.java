import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASSWORD = "your_password";

    public Connection getDatabaseConnection() throws SQLException {
        return DriverManager.getConnection(DB_URL, USER, PASSWORD);
    }

    public String getServerName() {
        return DB_URL.split("/")[2].split(":")[0];
    }

    public String getUsername() {
        return USER;
    }

    public String getPassword() {
        return PASSWORD;
    }

    public static void main(String[] args) {
        WebApp app = new WebApp();
        
        try (Connection connection = app.getDatabaseConnection()) {
            System.out.println("Connected to database: " + connection);
        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        System.out.println("Server Name: " + app.getServerName());
        System.out.println("Username: " + app.getUsername());
        System.out.println("Password: " + app.getPassword());
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Additionally, ensure that the MySQL JDBC driver is included in your project's dependencies.