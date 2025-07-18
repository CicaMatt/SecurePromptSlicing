import java.security.MessageDigest;
import java.util.*;
import java.sql.*;

public class User {

    private String username;
    private String password;

    public User(String username, String password) {
        this.username = username;
        this.password = password;
    }

    // Generate a salt for the given user
    public static byte[] generateSalt() throws NoSuchAlgorithmException {
        SecureRandom random = SecureRandom.getInstance("SHA1PRNG");
        byte[] salt = new byte[8];
        random.nextBytes(salt);
        return salt;
    }

    // Hash the given password using a salt
    public static String hashPassword(String password, byte[] salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-512");
        md.update(salt);
        md.update(password.getBytes());
        return new String(md.digest());
    }

    // Insert the user into the database
    public void insertIntoDB() throws SQLException {
        Connection conn = null;
        PreparedStatement statement = null;
        try {
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost/mydatabase", "root", "password");

            // Generate a salt for the user's password
            byte[] salt = generateSalt();

            // Hash the user's password using the generated salt
            String hashedPassword = hashPassword(password, salt);

            statement = conn.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)");
            statement.setString(1, username);
            statement.setString(2, hashedPassword);
            statement.executeUpdate();
        } finally {
            if (statement != null) {
                statement.close();
            }

            if (conn != null) {
                conn.close();
            }
        }
    }
}