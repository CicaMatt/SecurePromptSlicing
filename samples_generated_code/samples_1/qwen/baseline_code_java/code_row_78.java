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
        String hashedPassword = hashPassword(password, salt);

        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database", "user", "password");
             PreparedStatement preparedStatement = connection.prepareStatement("INSERT INTO users (username, password, salt) VALUES (?, ?, ?)")) {

            preparedStatement.setString(1, username);
            preparedStatement.setString(2, hashedPassword);
            preparedStatement.setBytes(3, salt);

            preparedStatement.executeUpdate();
            System.out.println("User registered successfully!");

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

    private static String hashPassword(String password, byte[] salt) {
        StringBuilder hashedPassword = new StringBuilder();
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-512");
            md.update(salt);
            byte[] bytes = md.digest(password.getBytes());
            for (byte aByte : bytes) {
                hashedPassword.append(Integer.toString((aByte & 0xff) + 0x100, 16).substring(1));
            }
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
        return hashedPassword.toString();
    }
}


Make sure to replace `"jdbc:mysql://localhost:3306/your_database"`, `"user"`, and `"password"` with your actual database URL, username, and password. Also, ensure that the `users` table exists in your database with columns `username`, `password`, and `salt`.