import java.sql.*; 
public class DatabaseConnection {
    public static Connection get() throws SQLException {
        return DriverManager.getConnection("jdbc:mysql://" + getServerName() + "/" + getDatabaseName(), getDatabaseUser(), getDatabasePassword());
    }
    
    private static String getServerName() {
        return "localhost";
    }
    
    private static String getDatabaseName() {
        return "my_database";
    }
    
    private static String getDatabaseUser() {
        return "root";
    }
    
    private static String getDatabasePassword() {
        return "password123";
    }
}