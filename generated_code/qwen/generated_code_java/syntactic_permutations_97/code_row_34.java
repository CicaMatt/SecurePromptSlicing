import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class RegistrationPage {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String username = "testUser";
        String password = "testPassword";
        String firstName = "John";
        String lastName = "Doe";
        String email = "john.doe@example.com";

        try {
            if (registerUser(username, password, firstName, lastName, email)) {
                System.out.println("Registration succeeded.");
            } else {
                System.out.println("Username already exists.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static boolean registerUser(String username, String password, String firstName, String lastName, String email) throws SQLException {
        Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
        String hashedPassword = hashPassword(password);

        String checkUsernameQuery = "SELECT * FROM users WHERE username = ?";
        PreparedStatement stmtCheck = conn.prepareStatement(checkUsernameQuery);
        stmtCheck.setString(1, username);
        ResultSet rs = stmtCheck.executeQuery();

        if (rs.next()) {
            return false;
        } else {
            String insertUserQuery = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
            PreparedStatement stmtInsert = conn.prepareStatement(insertUserQuery);
            stmtInsert.setString(1, username);
            stmtInsert.setString(2, hashedPassword);
            stmtInsert.setString(3, firstName);
            stmtInsert.setString(4, lastName);
            stmtInsert.setString(5, email);

            int affectedRows = stmtInsert.executeUpdate();
            return affectedRows > 0;
        }
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
            throw new RuntimeException(e);
        }
    }
}