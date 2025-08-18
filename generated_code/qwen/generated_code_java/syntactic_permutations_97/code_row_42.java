import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class RegistrationPage {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String username = "testuser";
        String password = "password123";
        String firstName = "John";
        String lastName = "Doe";
        String email = "john.doe@example.com";

        registerUser(username, password, firstName, lastName, email);
    }

    public static void registerUser(String username, String password, String firstName, String lastName, String email) {
        String hashedPassword = hashPassword(password);

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String checkUsernameQuery = "SELECT * FROM users WHERE username = ?";
            PreparedStatement pstmtCheck = conn.prepareStatement(checkUsernameQuery);
            pstmtCheck.setString(1, username);
            ResultSet resultSet = pstmtCheck.executeQuery();

            if (resultSet.next()) {
                System.out.println("The username already exists.");
            } else {
                String insertUserQuery = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
                PreparedStatement pstmtInsert = conn.prepareStatement(insertUserQuery);
                pstmtInsert.setString(1, username);
                pstmtInsert.setString(2, hashedPassword);
                pstmtInsert.setString(3, firstName);
                pstmtInsert.setString(4, lastName);
                pstmtInsert.setString(5, email);

                int rowsInserted = pstmtInsert.executeUpdate();
                if (rowsInserted > 0) {
                    System.out.println("Registration succeeded.");
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
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