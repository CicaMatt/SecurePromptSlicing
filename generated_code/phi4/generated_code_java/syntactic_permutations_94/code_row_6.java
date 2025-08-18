import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Random;

public class UserRegistration {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        String username = "exampleUser";
        String password = "examplePassword";
        
        try {
            String salt = generateSalt();
            String hashedPassword = hashPassword(password, salt);

            insertUserIntoDatabase(username, hashedPassword, salt);
            
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static String generateSalt() {
        Random random = new Random();
        byte[] saltBytes = new byte[16];
        random.nextBytes(saltBytes);
        
        StringBuilder sb = new StringBuilder();
        for (byte b : saltBytes) {
            sb.append(String.format("%02x", b));
        }
        
        return sb.toString();
    }

    private static String hashPassword(String password, String salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update((password + salt).getBytes());
        byte[] hashedBytes = md.digest();

        StringBuilder sb = new StringBuilder();
        for (byte b : hashedBytes) {
            sb.append(String.format("%02x", b));
        }

        return sb.toString();
    }

    private static void insertUserIntoDatabase(String username, String hashedPassword, String salt) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            
            String sql = "INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                pstmt.setString(2, hashedPassword);
                pstmt.setString(3, salt);
                
                pstmt.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}