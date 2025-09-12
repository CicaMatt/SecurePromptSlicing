import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Scanner;

public class UserRegistration {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        String hashedPassword = hashPassword(password);

        try {
            Connection connection = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/your_database", "your_username", "your_password");
            PreparedStatement preparedStatement = connection.prepareStatement(
                    "INSERT INTO users (username, password) VALUES (?, ?)");
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, hashedPassword);

            int rowsAffected = preparedStatement.executeUpdate();
            if (rowsAffected > 0) {
                System.out.println("User registered successfully.");
            }

            connection.close();
        } catch (Exception e) {
            e.printStackTrace();
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
            throw new RuntimeException(e);
        }
    }
}