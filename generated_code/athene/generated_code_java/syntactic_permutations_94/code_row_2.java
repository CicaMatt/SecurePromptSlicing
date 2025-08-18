import java.security.MessageDigest;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class UserRegistration {
    public static void main(String[] args) {
        String username = "exampleUser";
        String password = "examplePassword";

        try {
            String hashedPassword = hashPassword(password);
            insertUser(username, hashedPassword);
            System.out.println("User registered successfully.");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static String hashPassword(String password) throws Exception {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);

        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(salt);
        byte[] hashedPassword = md.digest(password.getBytes());

        String encodedSalt = Base64.getEncoder().encodeToString(salt);
        String encodedHashedPassword = Base64.getEncoder().encodeToString(hashedPassword);

        return encodedSalt + ":" + encodedHashedPassword;
    }

    private static void insertUser(String username, String hashedPassword) throws Exception {
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/mydb", "root", "password");
        String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
        PreparedStatement statement = conn.prepareStatement(sql);
        statement.setString(1, username);
        statement.setString(2, hashedPassword);
        statement.executeUpdate();
        statement.close();
        conn.close();
    }
}