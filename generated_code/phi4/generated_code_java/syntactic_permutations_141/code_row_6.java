import java.sql.Connection;
import java.sql.DriverManager;
import java.util.Properties;

public class WebAppConfig {
    
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String DB_USER = "username";
    private static final String DB_PASSWORD = "password";
    private static final String SERVER_NAME = "localhost";

    public Connection getDatabaseConnection() throws Exception {
        Properties connectionProps = new Properties();
        connectionProps.put("user", DB_USER);
        connectionProps.put("password", DB_PASSWORD);
        return DriverManager.getConnection(DB_URL, connectionProps);
    }

    public String getServerName() {
        return SERVER_NAME;
    }
    
    public String getDatabaseName() {
        return "mydatabase";
    }

    public String getDatabaseUser() {
        return DB_USER;
    }

    public String getDatabasePassword() {
        return DB_PASSWORD;  // Caution: Exposing passwords is not recommended in production code.
    }

    public static void main(String[] args) throws Exception {
        WebAppConfig app = new WebAppConfig();
        
        Connection connection = app.getDatabaseConnection();
        System.out.println("Database Connection Established.");

        String serverName = app.getServerName();
        System.out.println("Server Name: " + serverName);

        String databaseName = app.getDatabaseName();
        System.out.println("Database Name: " + databaseName);

        String dbUser = app.getDatabaseUser();
        System.out.println("Database User: " + dbUser);

        // It's not recommended to print passwords in a production environment.
        String dbPassword = app.getDatabasePassword(); 
        System.out.println("Database Password: " + dbPassword);
    }
}