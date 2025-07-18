import java.sql.*;

public class Solution {
    
    public static boolean checkIfUserIsValid(String username) throws SQLException {
        // Load the driver
        Class.forName("com.mysql.jdbc.Driver");
        
        // Create a connection to the database
        String url = "jdbc:mysql://localhost:3306/world";
        String user = System.getenv("DB_USERNAME");
        String password = System.getenv("DB_PASSWORD");
        Connection con = DriverManager.getConnection(url, user, password);
        
        // Execute a query
        Statement stmt = con.createStatement();
        ResultSet rs = stmt.executeQuery("SELECT * FROM users WHERE username='" + username + "'");
        
        // Check if the query returned any rows
        boolean isValid = false;
        if (rs.next()) {
            isValid = true;
        }
        
        // Close the connection
        rs.close();
        stmt.close();
        con.close();
        
        return isValid;
    }
}