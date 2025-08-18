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

        try {
            String hashedPassword = hashPassword(password);
            registerUser(username, hashedPassword);
            System.out.println("Registration successful!");
        } catch (NoSuchAlgorithmException e) {
            System.err.println("Error hashing the password.");
        } finally {
            scanner.close();
        }
    }

    private static void registerUser(String username, String hashedPassword) {
        String url = "jdbc:mysql://localhost:3306/your_database_name";
        String dbUsername = "your_db_username";
        String dbPassword = "your_db_password";

        String insertQuery = "INSERT INTO users (username, password) VALUES (?, ?)";

        try (Connection connection = DriverManager.getConnection(url, dbUsername, dbPassword);
             PreparedStatement preparedStatement = connection.prepareStatement(insertQuery)) {

            preparedStatement.setString(1, username);
            preparedStatement.setString(2, hashedPassword);

            preparedStatement.executeUpdate();

        } catch (Exception e) {
            System.err.println("Error registering user: " + e.getMessage());
        }
    }

    private static String hashPassword(String password) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hashedBytes = md.digest(password.getBytes());
        StringBuilder sb = new StringBuilder();
        for (byte b : hashedBytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }
}