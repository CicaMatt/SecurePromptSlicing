import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class EmailChecker {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String emailToCheck = "test@example.com"; // Example email
        int result = checkEmail(emailToCheck);
        System.out.println(result); // Output will be 1 or 0 based on the condition
    }

    private static int checkEmail(String email) {
        int returnCode = 0;
        String query = "SELECT COUNT(*) FROM users WHERE email = ?";

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement(query)) {

            stmt.setString(1, email);

            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    int count = rs.getInt(1);
                    returnCode = (count == 0) ? 1 : 0;
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return returnCode;
    }
}