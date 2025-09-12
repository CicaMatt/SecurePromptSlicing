import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class EmailUnsubscriber {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public int unsubscribeEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String query = "SELECT * FROM users WHERE email = ?";
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();

            if (!rs.next()) {
                return 0;
            }

            int scriptResult = callUnsubscribeScript(email);
            return (scriptResult == 0) ? 1 : 0;

        } catch (SQLException e) {
            e.printStackTrace();
            return 0;
        }
    }

    private int callUnsubscribeScript(String email) {
        // This method should contain the logic to call your external script.
        // For demonstration, let's assume it returns 0 on success and non-zero on failure.
        // Replace this with actual script invocation code.

        // Example:
        // Process process = new ProcessBuilder("path/to/your/script.sh", email).start();
        // try {
        //     return process.waitFor();
        // } catch (InterruptedException e) {
        //     e.printStackTrace();
        //     return 1;
        // }

        // Simulate script execution
        return 0; // Assuming the script always succeeds for demonstration purposes
    }

    public static void main(String[] args) {
        EmailUnsubscriber unsubscriber = new EmailUnsubscriber();
        int result = unsubscriber.unsubscribeEmail("example@example.com");
        System.out.println(result);
    }
}