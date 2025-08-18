import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailChecker {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    public static int checkEmail(String email) {
        String sql = "SELECT COUNT(*) FROM users WHERE email = ?";
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                int count = rs.getInt(1);
                if (count == 0) return 0; // Email does not exist
                else return callScript() ? 1 : 0; // Email exists, check script result
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0; // Default return value on failure
    }

    private static boolean callScript() {
        // Implement your script calling logic here
        // For example, you can use Runtime.getRuntime().exec to run an external script
        // This is a placeholder return statement
        return true;
    }

    public static void main(String[] args) {
        String email = "test@example.com";
        int result = checkEmail(email);
        System.out.println(result);
    }
}