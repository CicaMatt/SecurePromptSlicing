import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Base64;

public class Registration {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {

            // Register a new user
            registerUser(conn, "username", "password123");

            // Verify login
            boolean isValidLogin = verifyLogin(conn, "username", "password123");
            System.out.println("Is valid login: " + isValidLogin);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void registerUser(Connection conn, String username, String password) throws Exception {
        byte[] salt = generateSalt();
        String hashedPasswordWithSalt = hashPassword(password, salt);
        
        try (PreparedStatement stmt = conn.prepareStatement("INSERT INTO users (username, password_with_salt) VALUES (?, ?)")) {
            stmt.setString(1, username);
            stmt.setString(2, hashedPasswordWithSalt);
            stmt.executeUpdate();
        }
    }

    private static boolean verifyLogin(Connection conn, String username, String password) throws Exception {
        try (PreparedStatement stmt = conn.prepareStatement("SELECT password_with_salt FROM users WHERE username = ?")) {
            stmt.setString(1, username);

            ResultSet rs = stmt.executeQuery();

            if (rs.next()) {
                String storedHashedPasswordWithSalt = rs.getString("password_with_salt");
                
                // Extract salt and hashed password
                byte[] decoded = Base64.getDecoder().decode(storedHashedPasswordWithSalt);
                byte[] saltFromStorage = new byte[16];
                System.arraycopy(decoded, 0, saltFromStorage, 0, saltFromStorage.length);
                String storedHashedPassword = new String(decoded, 16, decoded.length - 16);

                // Hash the input password with extracted salt
                String hashedInputPasswordWithSalt = hashPassword(password, saltFromStorage);

                return storedHashedPassword.equals(hashedInputPasswordWithSalt.substring(32));
            }
        }
        return false;
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
        
        // Prepend the salt to the hashed password
        byte[] result = new byte[salt.length + hashedPassword.length];
        System.arraycopy(salt, 0, result, 0, salt.length);
        System.arraycopy(hashedPassword, 0, result, salt.length, hashedPassword.length);

        return Base64.getEncoder().encodeToString(result);
    }
}