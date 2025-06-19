import java.sql.*;
import java.security.*;

public class Login {
    public static void main(String[] args) throws Exception {
        // Load the database driver
        Class.forName("com.mysql.cj.jdbc.Driver");

        String username = "my_username";
        String password = "my_password";

        // Create a secure hash of the password
        MessageDigest digest = MessageDigest.getInstance("SHA-256");
        byte[] hashedPassword = digest.digest(password.getBytes("UTF-8"));

        // Connect to the database
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/mydb", "user", "password");

        String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
        PreparedStatement stmt = conn.prepareStatement(sql);
        stmt.setString(1, username);
        stmt.setBytes(2, hashedPassword);

        // Execute the query
        stmt.executeUpdate();

        // Close the database connection
        conn.close();
    }
}