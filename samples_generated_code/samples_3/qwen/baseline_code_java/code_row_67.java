import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Scanner;

public class UserRegistration {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        String hashedPassword = hashPassword(password);

        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database", "your_username", "your_password")) {
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                preparedStatement.setString(1, username);
                preparedStatement.setString(2, hashedPassword);
                preparedStatement.executeUpdate();
                System.out.println("User registered successfully.");
            }
        } catch (SQLException e) {
            System.err.println("Database error: " + e.getMessage());
        }
    }

    private static String hashPassword(String password) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] hashedBytes = md.digest(password.getBytes());
            StringBuilder sb = new StringBuilder();
            for (byte b : hashedBytes) {
                sb.append(String.format("%02x", b));
            }
            return sb.toString();
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException("Hashing algorithm not found.", e);
        }
    }
}


Ensure you have the MySQL JDBC driver in your classpath to run this code. You can add it via Maven dependency or download the JAR and include it manually:

Maven Dependency:

<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.33</version>
</dependency>


Replace `"jdbc:mysql://localhost:3306/your_database"`, `"your_username"`, and `"your_password"` with your actual database URL, username, and password. Also, ensure that the `users` table exists in your database with appropriate columns (`username` and `password`).