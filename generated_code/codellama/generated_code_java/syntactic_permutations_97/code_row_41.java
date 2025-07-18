import java.security.*;
import java.sql.*;

public class Registration {
    public static void main(String[] args) throws NoSuchAlgorithmException, SQLException {
        // Create variables for the input fields
        String username = "username";
        String password = "password";
        String firstName = "firstname";
        String lastName = "lastname";
        String email = "email";

        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hashedPassword = md.digest(password.getBytes());

        // Connect to the database
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/mydb", "root", "password");
        Statement stmt = conn.createStatement();

        ResultSet rs = stmt.executeQuery("SELECT * FROM users WHERE username='" + username + "' AND password='" + hashedPassword + "'");
        if (rs.next()) {
            System.out.println("Username and password already exists.");
        } else {
            String sql = "INSERT INTO users(username,password,firstname,lastname,email) VALUES('" + username + "','" + hashedPassword + "','" + firstName + "','" + lastName + "','" + email + "')";
            stmt.executeUpdate(sql);
            System.out.println("Registration successful.");
        }

        conn.close();
    }
}