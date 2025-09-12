import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class RegistrationForm {

    private static final String DB_URL = "jdbc:sqlite:registration.db";
    
    public static void main(String[] args) {
        createTable();
        
        String username = "user123"; // Example input
        String password = "password!"; // Example input
        
        registerUser(username, password);
    }

    private static void createTable() {
        try (Connection conn = DriverManager.getConnection(DB_URL)) {
            if (conn != null) {
                String sql = "CREATE TABLE IF NOT EXISTS users (\n"
                            + " id integer PRIMARY KEY,\n"
                            + " username text NOT NULL UNIQUE,\n"
                            + " hashed_password text NOT NULL\n"
                            + ");";
                
                try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                    pstmt.execute();
                }
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    private static void registerUser(String username, String password) {
        String hashedPassword;
        try {
            hashedPassword = hashPassword(password);
        } catch (NoSuchAlgorithmException e) {
            System.err.println("Hashing algorithm not found: " + e.getMessage());
            return;
        }

        String salt = generateSalt();
        String storedValue = salt + hashedPassword;

        String sql = "INSERT INTO users(username, hashed_password) VALUES(?, ?)";

        try (Connection conn = DriverManager.getConnection(DB_URL);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            
            pstmt.setString(1, username);
            pstmt.setString(2, storedValue);

            pstmt.executeUpdate();
            System.out.println("User registered successfully.");
        
        } catch (SQLException e) {
            System.err.println(e.getMessage());
        }
    }

    private static String hashPassword(String password) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hashedBytes = md.digest(password.getBytes());

        StringBuilder sb = new StringBuilder();
        for (byte b : hashedBytes) {
            sb.append(String.format("%02x", b));
        }
        
        return sb.toString();
    }

    private static String generateSalt() {
        // Simple salt generation, should be improved with a more robust method in production
        int randomInt = (int) (Math.random() * 1000);
        return Integer.toString(randomInt);
    }
}