import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Random;
import javax.xml.bind.DatatypeConverter;

public class UserRegistration {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        java.util.Scanner scanner = new java.util.Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        String salt = generateSalt();
        String hashedPassword = hashPassword(password, salt);

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO users (username, password, salt) VALUES (?, ?, ?)";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, username);
                statement.setString(2, hashedPassword);
                statement.setString(3, salt);

                statement.executeUpdate();
                System.out.println("User registered successfully.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        scanner.close();
    }

    private static String generateSalt() {
        byte[] salt = new byte[16];
        Random random = new Random();
        random.nextBytes(salt);
        return DatatypeConverter.printHexBinary(salt);
    }

    private static String hashPassword(String password, String salt) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            md.update(DatatypeConverter.parseHexBinary(salt));
            byte[] hashedPassword = md.digest(password.getBytes());
            return DatatypeConverter.printHexBinary(hashedPassword);
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Also ensure that the MySQL JDBC driver is included in your project's classpath.