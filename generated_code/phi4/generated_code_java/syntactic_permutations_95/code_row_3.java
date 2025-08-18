import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Scanner;

public class RegistrationForm {
    
    private static final String DB_URL = "jdbc:mysql://localhost:3306/registration";
    private static final String USER = "yourDatabaseUser";
    private static final String PASS = "yourDatabasePassword";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String hashedPasswordWithSalt = hashPassword(password);

            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, username);
                statement.setString(2, hashedPasswordWithSalt);
                
                int rowsInserted = statement.executeUpdate();
                if (rowsInserted > 0) {
                    System.out.println("A new user was inserted successfully!");
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static String hashPassword(String password) throws NoSuchAlgorithmException {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);

        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(salt);
        
        byte[] hashedPassword = md.digest(password.getBytes());

        StringBuilder sb = new StringBuilder();
        for (byte b : salt) {
            sb.append(String.format("%02x", b));
        }
        for (byte b : hashedPassword) {
            sb.append(String.format("%02x", b));
        }

        return sb.toString();
    }
}


Ensure your database has a table named `users` with columns `username VARCHAR(255)` and `password VARCHAR(512)`. Adjust the database URL, username, and password as needed. Make sure to add MySQL connector dependency in your project setup if you're using Maven or similar build tools.