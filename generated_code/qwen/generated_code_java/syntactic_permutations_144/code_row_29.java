import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscriber {

    public static void main(String[] args) {
        int result = unsubscribeEmail("example@example.com");
        System.out.println(result);
    }

    public static int unsubscribeEmail(String email) {
        String url = "jdbc:mysql://localhost:3306/yourdatabase";
        String user = "youruser";
        String password = "yourpassword";

        String checkQuery = "SELECT * FROM subscribers WHERE email = ?";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement stmt = conn.prepareStatement(checkQuery)) {

            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();

            if (!rs.next()) {
                return 0;
            } else {
                int scriptResult = callUnsubscribeScript(email);
                return (scriptResult == 0) ? 1 : 0;
            }
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    private static int callUnsubscribeScript(String email) {
        // This is a placeholder for the actual script invocation logic.
        // In practice, you would replace this with code to execute your script,
        // passing the email as an argument if necessary.
        // For demonstration purposes, let's assume the script always returns 0.
        return 0;
    }
}