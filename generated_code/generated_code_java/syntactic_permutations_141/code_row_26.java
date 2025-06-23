import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class DBConnection {

    private static final String USER = "admin";
    private static final String PASSWORD = "password123456";
    private static final String CONN_STRING = "jdbc:mysql://localhost/mydatabase";
    
    public static Connection getConnection() throws SQLException {
        return DriverManager.getConnection(CONN_STRING, USER, PASSWORD);
    }
}