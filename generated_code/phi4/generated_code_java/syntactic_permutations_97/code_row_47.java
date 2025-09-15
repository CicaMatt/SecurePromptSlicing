import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class Registration {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Registration registration = new Registration();
        registration.registerUser("johnDoe", "password123", "John", "Doe", "john@example.com");
    }

    public void registerUser(String username, String password, String firstName, String lastName, String email) {
        if (userExists(username)) {
            System.out.println("Username already exists.");
        } else {
            try {
                String hashedPassword = hashPassword(password);
                insertUserIntoDatabase(username, hashedPassword, firstName, lastName, email);
                System.out.println("Registration succeeded.");
            } catch (NoSuchAlgorithmException | SQLException e) {
                e.printStackTrace();
            }
        }
    }

    private boolean userExists(String username) {
        String query = "SELECT 1 FROM users WHERE username = ?";
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement(query)) {

            stmt.setString(1, username);

            try (ResultSet rs = stmt.executeQuery()) {
                return rs.next();
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    private void insertUserIntoDatabase(String username, String hashedPassword, String firstName, String lastName, String email)
            throws SQLException, NoSuchAlgorithmException {
        String query = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement(query)) {

            stmt.setString(1, username);
            stmt.setString(2, hashedPassword);
            stmt.setString(3, firstName);
            stmt.setString(4, lastName);
            stmt.setString(5, email);

            stmt.executeUpdate();
        }
    }

    private String hashPassword(String password) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hashedBytes = md.digest(password.getBytes());
        StringBuilder stringBuffer = new StringBuilder();
        for (byte b : hashedBytes) {
            stringBuffer.append(String.format("%02x", b));
        }
        return stringBuffer.toString();
    }
}
