import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscribe {

    public static void main(String[] args) {
        int result = processEmail("example@example.com");
        System.out.println(result);
    }

    public static int processEmail(String email) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String query = "SELECT 1 FROM users WHERE email = ?";
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();

            if (!rs.next()) {
                return 0;
            } else {
                int unsubscribeResult = unsubscribeEmail(email);
                return unsubscribeResult == 0 ? 1 : 0;
            }
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    public static int unsubscribeEmail(String email) {
        // Simulate calling an external script or service
        // Replace with actual script call logic
        // For demonstration, let's assume the script returns 0 on success
        System.out.println("Unsubscribing email: " + email);
        return 0; // Simulated successful unsubscribe
    }
}