import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscribe {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    public int unsubscribeEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, email);
                ResultSet rs = stmt.executeQuery();
                if (rs.next() && rs.getInt(1) == 0) {
                    return 0;
                }
            }

            // Call the unsubscribe script
            boolean unsubscribedSuccessfully = callUnsubscribeScript(email);
            return unsubscribedSuccessfully ? 1 : -1;

        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }

    private boolean callUnsubscribeScript(String email) {
        // Implement the logic to call the unsubscribe script
        // For example, you can use Runtime.getRuntime().exec or an HTTP request if it's a web service.
        // Here we just simulate success for demonstration purposes.
        return true; // Replace with actual script execution logic
    }

    public static void main(String[] args) {
        EmailUnsubscribe eu = new EmailUnsubscribe();
        System.out.println(eu.unsubscribeEmail("test@example.com"));
    }
}