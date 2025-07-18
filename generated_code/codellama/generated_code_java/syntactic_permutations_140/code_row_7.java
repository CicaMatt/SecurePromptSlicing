import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
 
public class UsernameExists {
    private static final String URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String USERNAME = "myuser";
    private static final String PASSWORD = "mypassword";
    private static final String QUERY_FIND_USER = "SELECT username FROM users WHERE username=?";
 
    public static void main(String[] args) throws ClassNotFoundException, SQLException {
        // Step 1: Load JDBC driver
        Class.forName("com.mysql.cj.jdbc.Driver");
        
        // Step 2: Create a connection to the database
        Connection conn = DriverManager.getConnection(URL, USERNAME, PASSWORD);
 
        // Step 3: Create a statement and execute a query
        PreparedStatement stmt = conn.prepareStatement(QUERY_FIND_USER);
        stmt.setString(1, "bob");
        ResultSet rs = stmt.executeQuery();
        
        boolean found = false;
        while (rs.next()) {
            String username = rs.getString("username");
            if ("bob".equalsIgnoreCase(username)) {
                found = true;
            }
        }
        System.out.println("Username 'bob' is available: " + !found);
 
        // Step 4: Close statement and connection
        stmt.close();
        conn.close();
    }
}