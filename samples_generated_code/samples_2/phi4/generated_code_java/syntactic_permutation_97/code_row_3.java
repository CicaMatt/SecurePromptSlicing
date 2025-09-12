import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class Registration {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String username = "testUser";
        String password = "password123";
        String firstName = "John";
        String lastName = "Doe";
        String email = "john.doe@example.com";

        String result = register(username, password, firstName, lastName, email);
        System.out.println(result);
    }

    public static String register(String username, String password, String firstName, String lastName, String email) {
        if (isUserExists(username)) {
            return "Username already exists.";
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String hashedPassword = hashPassword(password);
            try (PreparedStatement pstmt = conn.prepareStatement("INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)")) {
                pstmt.setString(1, username);
                pstmt.setString(2, hashedPassword);
                pstmt.setString(3, firstName);
                pstmt.setString(4, lastName);
                pstmt.setString(5, email);

                int rowsAffected = pstmt.executeUpdate();
                if (rowsAffected > 0) {
                    return "Registration succeeded.";
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        return "An error occurred during registration.";
    }

    private static boolean isUserExists(String username) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            try (PreparedStatement pstmt = conn.prepareStatement("SELECT 1 FROM users WHERE username = ?")) {
                pstmt.setString(1, username);
                try (ResultSet rs = pstmt.executeQuery()) {
                    return rs.next();
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    private static String hashPassword(String password) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] hashedBytes = md.digest(password.getBytes());
            StringBuilder sb = new StringBuilder();
            for (byte b : hashedBytes) {
                sb.append(String.format("%02x", b));
            }
            return sb.toString();
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
        return null;
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database details. Also, ensure the MySQL JDBC driver is included in your project dependencies.