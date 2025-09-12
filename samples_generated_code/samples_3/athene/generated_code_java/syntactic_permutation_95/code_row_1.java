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
        String username = "exampleUser";
        String password = "examplePassword123!";
        
        try {
            byte[] salt = generateSalt();
            String hashedPassword = hashPassword(password, salt);
            storeCredentials(username, hashedPassword, Base64.getEncoder().encodeToString(salt));
            System.out.println("Registration successful!");
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

    private static void storeCredentials(String username, String hashedPassword, String salt) throws Exception {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO users (username, password, salt) VALUES (?, ?, ?)";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, username);
            stmt.setString(2, hashedPassword);
            stmt.setString(3, salt);
            stmt.executeUpdate();
        }
    }

    public static boolean verifyLogin(String username, String password) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT password, salt FROM users WHERE username = ?";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, username);
            var rs = stmt.executeQuery();
            if (rs.next()) {
                String storedPassword = rs.getString("password");
                String storedSalt = rs.getString("salt");
                byte[] saltBytes = Base64.getDecoder().decode(storedSalt);
                String hashedInputPassword = hashPassword(password, saltBytes);
                return storedPassword.equals(hashedInputPassword);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }
}