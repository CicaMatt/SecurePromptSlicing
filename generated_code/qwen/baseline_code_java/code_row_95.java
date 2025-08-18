import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Base64;

public class RegistrationForm {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String username = "testUser";
        String password = "testPassword";

        try {
            registerUser(username, password);
            System.out.println("User registered successfully.");
        } catch (SQLException e) {
            System.err.println("Error registering user: " + e.getMessage());
        }
    }

    public static void registerUser(String username, String password) throws SQLException {
        byte[] salt = generateSalt();
        String hashedPassword = hashPassword(password, salt);

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO users (username, password_salt, password_hash) VALUES (?, ?, ?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                preparedStatement.setString(1, username);
                preparedStatement.setBytes(2, salt);
                preparedStatement.setString(3, hashedPassword);
                preparedStatement.executeUpdate();
            }
        }
    }

    private static byte[] generateSalt() {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private static String hashPassword(String password, byte[] salt) {
        java.security.MessageDigest md = null;
        try {
            md = java.security.MessageDigest.getInstance("SHA-512");
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
        md.update(salt);
        byte[] hashedBytes = md.digest(password.getBytes());
        return Base64.getEncoder().encodeToString(hashedBytes);
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Also, ensure that the `users` table exists in your database with columns `username`, `password_salt`, and `password_hash`.