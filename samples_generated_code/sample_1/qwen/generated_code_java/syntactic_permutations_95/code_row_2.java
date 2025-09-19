import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.PBEKeySpec;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class RegistrationForm {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/userdb";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public static void main(String[] args) {
        String username = "testuser";
        String password = "securePassword123";

        // Register user
        boolean registrationSuccess = registerUser(username, password);
        if (registrationSuccess) {
            System.out.println("Registration successful!");
        } else {
            System.out.println("Registration failed.");
        }

        // Login user
        boolean loginSuccess = loginUser(username, password);
        if (loginSuccess) {
            System.out.println("Login successful!");
        } else {
            System.out.println("Login failed.");
        }
    }

    private static boolean registerUser(String username, String password) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            byte[] salt = generateSalt();
            byte[] hashedPassword = hashPassword(password.toCharArray(), salt);

            String sql = "INSERT INTO users (username, password, salt) VALUES (?, ?, ?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                preparedStatement.setString(1, username);
                preparedStatement.setBytes(2, hashedPassword);
                preparedStatement.setBytes(3, salt);
                return preparedStatement.executeUpdate() > 0;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }

    private static boolean loginUser(String username, String password) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String sql = "SELECT password, salt FROM users WHERE username = ?";
            try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                preparedStatement.setString(1, username);
                ResultSet resultSet = preparedStatement.executeQuery();
                if (resultSet.next()) {
                    byte[] storedHashedPassword = resultSet.getBytes("password");
                    byte[] storedSalt = resultSet.getBytes("salt");
                    byte[] inputHashedPassword = hashPassword(password.toCharArray(), storedSalt);
                    return MessageDigest.isEqual(storedHashedPassword, inputHashedPassword);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }

    private static byte[] generateSalt() {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private static byte[] hashPassword(char[] password, byte[] salt) {
        PBEKeySpec spec = new PBEKeySpec(password, salt, 65536, 128);
        try {
            SecretKeyFactory skf = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA1");
            return skf.generateSecret(spec).getEncoded();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}
