import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class LoginService {
    
    public static void main(String[] args) throws SQLException{
        String username = "admin"; 
        String password = "1234567890"; 
        login(username,password);
    }

    public static boolean login(String username, String password) throws SQLException {
        // connect to database using JDBC driver.
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/myDb", "root", "password");

        // prepare the query and execute it on the db connection
        String query = "SELECT * FROM users WHERE username = ? AND password = ?";
        PreparedStatement stmt = conn.prepareStatement(query); 
        stmt.setString(1, username); 
        stmt.setString(2, password);
        ResultSet rs = stmt.executeQuery();

        // check if there is a record for the query. If yes, login successful
        boolean exists = false;
        while (rs.next()) {
            exists = true;
        } 
        return exists;
    }
}