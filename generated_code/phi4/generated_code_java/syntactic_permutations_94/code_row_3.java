import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Scanner;
import java.util.UUID;

public class UserRegistration {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String DB_USER = "your_username";
    private static final String DB_PASSWORD = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();
        
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String hashedPassword = hashPassword(password);
            
            if (hashedPassword != null) {
                insertUser(connection, username, hashedPassword);
                System.out.println("User registered successfully.");
            } else {
                System.err.println("Error hashing password.");
            }
        } catch (SQLException e) {
            System.err.println("Database error: " + e.getMessage());
        }

        scanner.close();
    }

    private static String hashPassword(String password) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");

            // Generate a random salt
            byte[] salt = UUID.randomUUID().toString().getBytes();
            md.update(salt);

            byte[] hashedPassword = md.digest(password.getBytes());

            // Combine salt and hashed password
            StringBuilder sb = new StringBuilder();
            for (byte b : salt) {
                sb.append(String.format("%02x", b));
            }
            for (byte b : hashedPassword) {
                sb.append(String.format("%02x", b));
            }

            return sb.toString();

        } catch (NoSuchAlgorithmException e) {
            System.err.println("Hashing algorithm error: " + e.getMessage());
            return null;
        }
    }

    private static void insertUser(Connection connection, String username, String hashedPassword) throws SQLException {
        String sql = "INSERT INTO users (username, password_hash) VALUES (?, ?)";
        
        try (PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setString(1, username);
            statement.setString(2, hashedPassword);
            statement.executeUpdate();
        }
    }
}


**Note:** 
- Replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password.
- Ensure the MySQL JDBC driver is included in your project's dependencies.