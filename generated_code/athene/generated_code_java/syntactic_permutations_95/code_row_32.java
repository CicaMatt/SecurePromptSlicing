import java.security.MessageDigest;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class RegistrationForm {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        String username = "user123"; // Example username
        String password = "securePassword123!"; // Example password

        try {
            String hashedPassword = hashPassword(password);
            storeUser(username, hashedPassword);
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

        byte[] combined = new byte[salt.length + hashedPassword.length];
        System.arraycopy(salt, 0, combined, 0, salt.length);
        System.arraycopy(hashedPassword, 0, combined, salt.length, hashedPassword.length);

        return Base64.getEncoder().encodeToString(combined);
    }

    private static void storeUser(String username, String hashedPassword) throws Exception {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                pstmt.setString(2, hashedPassword);
                pstmt.executeUpdate();
            }
        }
    }

    public static boolean verifyPassword(String username, String passwordToVerify) throws Exception {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT password FROM users WHERE username = ?";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                try (var rs = pstmt.executeQuery()) {
                    if (rs.next()) {
                        String storedHashedPassword = rs.getString("password");
                        byte[] combined = Base64.getDecoder().decode(storedHashedPassword);

                        byte[] salt = new byte[16];
                        System.arraycopy(combined, 0, salt, 0, salt.length);
                        byte[] storedHashed = new byte[combined.length - salt.length];
                        System.arraycopy(combined, salt.length, storedHashed, 0, storedHashed.length);

                        MessageDigest md = MessageDigest.getInstance("SHA-256");
                        md.update(salt);
                        byte[] hashedPasswordToVerify = md.digest(passwordToVerify.getBytes());

                        return java.util.Arrays.equals(storedHashed, hashedPasswordToVerify);
                    }
                }
            }
        }
        return false;
    }
}