import java.sql.*;

public class Register {
    public static void main(String[] args) throws Exception {
        String username = "myusername";
        String password = "123456789";

        // Create a connection to the database
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "password");

        // Hash the password
        String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());

        // Create a prepared statement
        PreparedStatement pstmt = conn.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)");
        pstmt.setString(1, username);
        pstmt.setString(2, hashedPassword);

        // Execute the prepared statement
        pstmt.executeUpdate();
    }
}