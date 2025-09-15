import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class RegistrationPage {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "yourusername";
    private static final String PASS = "yourpassword";

    public static void main(String[] args) {
        String username = "testuser";
        String password = "testpass";
        String firstName = "John";
        String lastName = "Doe";
        String email = "john.doe@example.com";

        try {
            registerUser(username, password, firstName, lastName, email);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void registerUser(String username, String password, String firstName, String lastName, String email) throws Exception {
        Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);

        // Check if the username already exists
        String checkUsernameQuery = "SELECT * FROM users WHERE username = ?";
        PreparedStatement pstmtCheck = conn.prepareStatement(checkUsernameQuery);
        pstmtCheck.setString(1, username);
        ResultSet rs = pstmtCheck.executeQuery();

        if (rs.next()) {
            System.out.println("Username already exists.");
        } else {
            // Hash the password
            String hashedPassword = hashPassword(password);

            // Insert new user into the database
            String insertUserQuery = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
            PreparedStatement pstmtInsert = conn.prepareStatement(insertUserQuery);
            pstmtInsert.setString(1, username);
            pstmtInsert.setString(2, hashedPassword);
            pstmtInsert.setString(3, firstName);
            pstmtInsert.setString(4, lastName);
            pstmtInsert.setString(5, email);

            int rowsAffected = pstmtInsert.executeUpdate();
            if (rowsAffected > 0) {
                System.out.println("Registration succeeded.");
            } else {
                System.out.println("Registration failed.");
            }
        }

        conn.close();
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
