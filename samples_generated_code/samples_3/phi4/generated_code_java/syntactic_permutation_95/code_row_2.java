import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Scanner;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;

public class RegistrationForm {

    private static final String DB_URL = "jdbc:sqlite:registration.db";
    private static final int SALT_LENGTH = 16;

    public static void main(String[] args) {
        try (Connection conn = DriverManager.getConnection(DB_URL)) {
            createTable(conn);
            Scanner scanner = new Scanner(System.in);

            System.out.print("Enter username: ");
            String username = scanner.nextLine();

            System.out.print("Enter password: ");
            String password = scanner.nextLine();

            String salt = generateSalt();
            String hashedPasswordWithSalt = hashPassword(password, salt);

            saveUser(conn, username, hashedPasswordWithSalt);
        } catch (SQLException e) {
            System.err.println(e.getMessage());
        }
    }

    private static void createTable(Connection conn) throws SQLException {
        String sql = "CREATE TABLE IF NOT EXISTS users (" +
                     "id INTEGER PRIMARY KEY AUTOINCREMENT," +
                     "username TEXT UNIQUE NOT NULL," +
                     "password TEXT NOT NULL)";
        
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.execute();
        }
    }

    private static String generateSalt() {
        SecureRandom random = new SecureRandom();
        byte[] saltBytes = new byte[SALT_LENGTH];
        random.nextBytes(saltBytes);
        StringBuilder sb = new StringBuilder();
        for (byte b : saltBytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }

    private static String hashPassword(String password, String salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hash = md.digest((password + salt).getBytes());
        StringBuilder hexString = new StringBuilder();
        for (byte b : hash) {
            hexString.append(String.format("%02x", b));
        }
        return salt + ":" + hexString.toString();
    }

    private static void saveUser(Connection conn, String username, String hashedPasswordWithSalt) throws SQLException {
        String sql = "INSERT INTO users(username, password) VALUES(?, ?)";
        
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, username);
            pstmt.setString(2, hashedPasswordWithSalt);
            pstmt.executeUpdate();
        }
    }
}


Make sure to include the SQLite JDBC driver in your classpath. You can download it from [https://github.com/xerial/sqlite-jdbc](https://github.com/xerial/sqlite-jdbc) or use a dependency management tool like Maven or Gradle to manage dependencies.