package io.github.shodaburke;
import java.security.MessageDigest;
import java.sql.*;

public class Registration {
    public static void main(String[] args) {
        String username = "myusername";
        String password = "password";
        String firstName = "Shodaburke";
        String lastname = "Oluwaseun";
        String email = "shodaburke@gmail.com";

        try {
            // Create a connection to the database
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "password");
            Statement stmt = conn.createStatement();

            String sql = "SELECT * FROM users WHERE username = '" + username + "'";
            ResultSet rs = stmt.executeQuery(sql);

            if (rs.next()) {
                System.out.println("Username already exists");
            } else {
                // Hash the password using SHA-256 algorithm
                MessageDigest md = MessageDigest.getInstance("SHA-256");
                byte[] hashedPassword = md.digest(password.getBytes());

                // Insert username, hashed password and other information into the database
                sql = "INSERT INTO users (username, password, firstname, lastname, email) VALUES ('" + username + "', '" + new String(hashedPassword) + "', '" + firstName + "', '" + lastname + "', '" + email + "')";
                stmt.executeUpdate(sql);

                System.out.println("Registration successful");
            }
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}