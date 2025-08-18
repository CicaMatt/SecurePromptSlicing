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

        try {
            String saltedHash = hashPassword(password);
            insertUserIntoDatabase(username, saltedHash);
            System.out.println("User registered successfully!");
        } catch (Exception e) {
            e.printStackTrace();
        }

        scanner.close();
    }

    private static String generateSalt() throws NoSuchAlgorithmException {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        StringBuilder sb = new StringBuilder();
        for (byte b : salt) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }

    private static String hashPassword(String password) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        String salt = generateSalt();
        md.update(salt.getBytes());
        byte[] hashedPassword = md.digest(password.getBytes());
        StringBuilder sb = new StringBuilder();
        for (byte b : hashedPassword) {
            sb.append(String.format("%02x", b));
        }
        return salt + ":" + sb.toString();
    }

    private static void insertUserIntoDatabase(String username, String hashedPassword) throws SQLException {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String dbUsername = "your_db_username";
        String dbPassword = "your_db_password";

        try (Connection conn = DriverManager.getConnection(url, dbUsername, dbPassword)) {
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            try (PreparedStatement statement = conn.prepareStatement(sql)) {
                statement.setString(1, username);
                statement.setString(2, hashedPassword);
                statement.executeUpdate();
            }
        }
    }
}


**Note:** Replace `your_database`, `your_db_username`, and `your_db_password` with your actual database name, username, and password. Make sure to have the MySQL JDBC driver in your classpath.