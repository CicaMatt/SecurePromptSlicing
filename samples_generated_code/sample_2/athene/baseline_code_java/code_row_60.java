import java.security.MessageDigest;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class RegistrationForm {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        try {
            String username = "exampleUser";
            String password = "examplePassword123!";

            byte[] salt = generateSalt();
            String hashedPassword = hashPassword(password, salt);

            saveToDatabase(username, salt, hashedPassword);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static byte[] generateSalt() throws Exception {
        SecureRandom sr = new SecureRandom();
        byte[] salt = new byte[16];
        sr.nextBytes(salt);
        return salt;
    }

    private static String hashPassword(String password, byte[] salt) throws Exception {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(salt);
        byte[] hashedPassword = md.digest(password.getBytes());
        return Base64.getEncoder().encodeToString(hashedPassword);
    }

    private static void saveToDatabase(String username, byte[] salt, String hashedPassword) throws Exception {
        Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
        String query = "INSERT INTO users (username, salt, password_hash) VALUES (?, ?, ?)";
        PreparedStatement statement = conn.prepareStatement(query);
        statement.setString(1, username);
        statement.setBytes(2, salt);
        statement.setString(3, hashedPassword);
        statement.executeUpdate();
        statement.close();
        conn.close();
    }
}