import java.io.Console;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class RegistrationForm {

    private static final String DB_URL = "jdbc:sqlite:users.db"; // SQLite for simplicity

    public static void main(String[] args) {
        Console console = System.console();
        if (console == null) {
            System.err.println("Console is not supported");
            return;
        }

        try (Connection connection = DriverManager.getConnection(DB_URL)) {
            createTable(connection);

            String username = console.readLine("Enter username: ");
            char[] passwordArray = console.readPassword("Enter password: ");
            String password = new String(passwordArray);

            registerUser(connection, username, password);
            System.out.println("Registration successful!");

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static void createTable(Connection connection) throws SQLException {
        String sql = "CREATE TABLE IF NOT EXISTS users (" +
                     "id INTEGER PRIMARY KEY AUTOINCREMENT," +
                     "username TEXT UNIQUE NOT NULL," +
                     "salted_hash TEXT NOT NULL" +
                     ");";
        try (PreparedStatement pstmt = connection.prepareStatement(sql)) {
            pstmt.execute();
        }
    }

    private static void registerUser(Connection connection, String username, String password) throws SQLException {
        byte[] salt = generateSalt();
        String saltedHash = hashPassword(password, salt);

        String sql = "INSERT INTO users(username, salted_hash) VALUES(?, ?)";
        try (PreparedStatement pstmt = connection.prepareStatement(sql)) {
            pstmt.setString(1, username);
            pstmt.setString(2, saltedHash);
            pstmt.executeUpdate();
        }
    }

    private static byte[] generateSalt() throws NoSuchAlgorithmException {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private static String hashPassword(String password, byte[] salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-512");
        md.update(salt);

        byte[] hashedPassword = md.digest(password.getBytes());
        StringBuilder sb = new StringBuilder();
        for (byte b : hashedPassword) {
            sb.append(String.format("%02x", b));
        }
        return salt.length + ":" + sb.toString();
    }
}


Note: This code uses SQLite for simplicity. You need to include the SQLite JDBC driver in your classpath to run this code.