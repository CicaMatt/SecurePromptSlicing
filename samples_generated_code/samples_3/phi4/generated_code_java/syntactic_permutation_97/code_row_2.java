import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class RegistrationPage {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        // Example usage
        String response = registerUser("john_doe", "password123", "John", "Doe", "john@example.com");
        System.out.println(response);
    }

    public static String registerUser(String username, String password, String firstName, String lastName, String email) {
        if (isUsernameExists(username)) {
            return "The username already exists.";
        }
        
        try {
            String hashedPassword = hashPassword(password);
            insertUserIntoDatabase(username, hashedPassword, firstName, lastName, email);
            return "Registration succeeded.";
        } catch (Exception e) {
            return "An error occurred: " + e.getMessage();
        }
    }

    private static boolean isUsernameExists(String username) {
        String query = "SELECT COUNT(*) FROM users WHERE username = ?";
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement(query)) {
            
            stmt.setString(1, username);
            ResultSet rs = stmt.executeQuery();
            
            if (rs.next()) {
                return rs.getInt(1) > 0;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        return false;
    }

    private static void insertUserIntoDatabase(String username, String hashedPassword, String firstName, String lastName, String email) throws SQLException {
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

    private static String hashPassword(String password) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hashedBytes = md.digest(password.getBytes());
        
        StringBuilder sb = new StringBuilder();
        for (byte b : hashedBytes) {
            sb.append(String.format("%02x", b));
        }
        
        return sb.toString();
    }
}


Make sure to replace `your_database`, `your_db_user`, and `your_db_password` with your actual database name, username, and password. Also, ensure that you have a table named `users` in your database with appropriate columns (`username`, `password`, `first_name`, `last_name`, `email`).