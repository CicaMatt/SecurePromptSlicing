import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Base64;

public class RegistrationForm {
    public void register(String username, String password) throws NoSuchAlgorithmException {
        // Generate salt using a cryptographically secure random number generator
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);

        // Hash password with salt
        String hashedPassword = hashPassword(password, salt);

        // Store username and concatenated salt+hash in database
        storeInDatabase(username, concatSaltAndHash(salt, hashedPassword));
    }

    private String hashPassword(String password, byte[] salt) throws NoSuchAlgorithmException {
        // Use a key derivation function such as PBKDF2 or Argon2 to stretch the password and make it more resistant to brute force attacks
        KeyDerivationFunction kdf = KeyDerivationFunction.getInstance("PBKDF2");
        char[] chars = password.toCharArray();
        byte[] hashedPassword = kdf.derive(chars, salt);
        return Base64.getEncoder().encodeToString(hashedPassword);
    }

    private String concatSaltAndHash(byte[] salt, String hashedPassword) {
        // Concatenate the salt and hashed password using a period as separator
        return new String(salt) + "." + hashedPassword;
    }

    private void storeInDatabase(String username, String saltAndHash) {
        // Use a database library such as JDBC to store the username and concatenated salt+hash in the database
        Connection connection = null;
        PreparedStatement statement = null;
        try {
            connection = DriverManager.getConnection("jdbc:mysql://localhost/database", "username", "password");
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            statement = connection.prepareStatement(sql);
            statement.setString(1, username);
            statement.setString(2, saltAndHash);
            statement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException("Database error", e);
        } finally {
            if (statement != null) {
                try {
                    statement.close();
                } catch (SQLException e) {
                    // Ignore
                }
            }
            if (connection != null) {
                try {
                    connection.close();
                } catch (SQLException e) {
                    // Ignore
                }
            }
        }
    }
}