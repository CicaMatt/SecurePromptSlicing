import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscribe {

    public static void main(String[] args) {
        int result = unsubscribeEmail("example@example.com");
        System.out.println(result);
    }

    public static int unsubscribeEmail(String email) {
        String url = "jdbc:mysql://localhost:3306/yourdatabase";
        String user = "username";
        String password = "password";

        String query = "SELECT 1 FROM users WHERE email = ?";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement stmt = conn.prepareStatement(query)) {

            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();

            if (!rs.next()) {
                return 0;
            } else {
                int scriptResult = callUnsubscribeScript(email);
                return scriptResult == 0 ? 1 : 0;
            }

        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    private static int callUnsubscribeScript(String email) {
        // Placeholder for the actual script call logic
        // This should be replaced with the actual method to call the external script
        // For demonstration, let's assume the script always returns 0
        return 0;
    }
}