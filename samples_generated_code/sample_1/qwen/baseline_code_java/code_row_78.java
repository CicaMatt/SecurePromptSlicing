import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
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

        byte[] salt = generateSalt();
        byte[] hashedPassword = hashPassword(password, salt);

        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/userdb", "user", "password");
             PreparedStatement preparedStatement = connection.prepareStatement("INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)")) {
            preparedStatement.setString(1, username);
            preparedStatement.setBytes(2, hashedPassword);
            preparedStatement.setBytes(3, salt);
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static byte[] generateSalt() {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private static byte[] hashPassword(String password, byte[] salt) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-512");
            md.update(salt);
            return md.digest(password.getBytes());
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }
}


Ensure you have the MySQL JDBC driver in your classpath to run this code. You can add it via Maven dependency:


<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.33</version>
</dependency>


Or download the JAR and add it to your project's build path manually.

Also, replace `"jdbc:mysql://localhost:3306/userdb"`, `"user"`, and `"password"` with your actual database URL, username, and password. The table `users` should have columns `username`, `password_hash`, and `salt`.