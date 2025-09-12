import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Scanner;

public class RegistrationForm {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            Scanner scanner = new Scanner(System.in);

            System.out.print("Enter username: ");
            String username = scanner.nextLine();

            System.out.print("Enter password: ");
            String password = scanner.nextLine();

            byte[] salt = generateSalt();
            String hashedPassword = hashPassword(password, salt);

            storeUser(connection, username, hashedPassword, salt);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static byte[] generateSalt() {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private static String hashPassword(String password, byte[] salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(salt);
        byte[] hashedPassword = md.digest(password.getBytes());
        StringBuilder sb = new StringBuilder();
        for (byte b : hashedPassword) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }

    private static void storeUser(Connection connection, String username, String hashedPassword, byte[] salt) throws Exception {
        String sql = "INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)";
        try (PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setString(1, username);
            statement.setString(2, hashedPassword);
            statement.setBytes(3, salt);

            statement.executeUpdate();
        }
    }
}