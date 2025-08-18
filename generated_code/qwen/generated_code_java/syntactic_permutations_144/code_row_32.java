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
        String user = "youruser";
        String password = "yourpassword";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String query = "SELECT * FROM subscribers WHERE email = ?";
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();

            if (!rs.next()) {
                return 0;
            } else {
                int scriptResult = runUnsubscribeScript(email);
                return (scriptResult == 0) ? 1 : 0;
            }
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    private static int runUnsubscribeScript(String email) {
        // Simulating a script call
        // Replace this with actual script execution logic
        System.out.println("Running unsubscribe script for: " + email);
        // Return 0 if the script is successful, any other value if not
        return 0; // Assuming success for demonstration purposes
    }
}