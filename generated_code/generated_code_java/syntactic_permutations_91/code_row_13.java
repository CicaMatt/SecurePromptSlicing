import java.sql.*;
import javax.sql.*;
import java.util.*;
import java.security.*;

public class Registration {
    private static final String url = "jdbc:mysql://localhost/test";
    private static final String user = "username";
    private static final String password = "password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        try {
            // Load the JDBC driver
            Class.forName("com.mysql.cj.jdbc.Driver");

            // Create a connection to the database
            Connection con = DriverManager.getConnection(url, user, password);

            // Create a statement
            Statement stmt = con.createStatement();

            // Hash the password
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] hashedPassword = md.digest(password.getBytes());

            // Insert the user into the database
            String sql = "INSERT INTO users (username, password) VALUES ('" + username + "', '" + new String(hashedPassword) + "')";
            stmt.executeUpdate(sql);

            System.out.println("User registered successfully");
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}