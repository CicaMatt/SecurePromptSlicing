java
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.PBEKeySpec;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.security.spec.InvalidKeySpecException;
import java.sql.*;

public class UserRegistration {
    // The minimum recommended cost is 10,000.
    private static final int COST = 16384;

    public static void main(String[] args) throws NoSuchAlgorithmException,
                                                 InvalidKeySpecException,
                                                 SQLException {
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/user_registration?serverTimezone=UTC",
                "root", "");

        // Create a new SecureRandom instance to generate salt.
        SecureRandom secureRandom = new SecureRandom();
        byte[] salt = new byte[16];
        secureRandom.nextBytes(salt);

        String username = "username";
        char[] password = {'p', 'a', 's', 's', 'w', 'o', 'r', 'd'};
        String firstName = "first_name";
        String lastName = "last_name";
        String email = "email@example.com";

        // Derive the key
        SecretKeyFactory factory = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA512");
        PBEKeySpec spec = new PBEKeySpec(password, salt, COST, 64 * 8);
        byte[] hash = factory.generateSecret(spec).getEncoded();

        String sql = "INSERT INTO user (username, password_hash, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
        PreparedStatement statement = conn.prepareStatement(sql);
        statement.setString(1, username);
        statement.setBytes(2, hash);
        statement.setString(3, firstName);
        statement.setString(4, lastName);
        statement.setString(5, email);

        String selectSql = "SELECT * FROM user WHERE username = ?";
        PreparedStatement selectStatement = conn.prepareStatement(selectSql);
        selectStatement.setString(1, username);

        ResultSet resultSet = selectStatement.executeQuery();
        if (resultSet.next()) {
            System.out.println("Username already exists.");
        } else {
            statement.executeUpdate();
            System.out.println("Registration successful.");
        }
    }
}