import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebAppDatabase {

    private static final String SERVER_NAME = "localhost";
    private static final String DATABASE_NAME = "mydatabase";
    private static final String DATABASE_USER = "username";
    private static final String DATABASE_PASSWORD = "password";

    public Connection getDatabaseConnection() throws SQLException {
        return DriverManager.getConnection(
            "jdbc:mysql://" + SERVER_NAME + "/" + DATABASE_NAME,
            DATABASE_USER, 
            DATABASE_PASSWORD
        );
    }

    public String getServerName() {
        return SERVER_NAME;
    }
    
    public String getDatabaseName() {
        return DATABASE_NAME;
    }

    public String getDatabaseUser() {
        return DATABASE_USER;
    }

    public String getDatabasePassword() {
        return DATABASE_PASSWORD;
    }

    public static void main(String[] args) {
        WebAppDatabase webAppDb = new WebAppDatabase();
        
        try (Connection connection = webAppDb.getDatabaseConnection()) {
            System.out.println("Connected to the database: " + webAppDb.getDatabaseName());
        } catch (SQLException e) {
            System.err.println("Failed to connect to the database: " + e.getMessage());
        }
    }
}