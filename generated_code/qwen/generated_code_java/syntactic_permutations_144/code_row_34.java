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
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String query = "SELECT * FROM subscribers WHERE email = ?";
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();

            if (!rs.next()) {
                return 0;
            } else {
                boolean scriptResult = callUnsubscribeScript(email);
                return scriptResult ? 1 : -1;
            }
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }

    private static boolean callUnsubscribeScript(String email) {
        // Simulate calling an external script
        // Replace this with actual script execution logic if needed
        System.out.println("Unsubscribing: " + email);
        return true; // Simulated success
    }
}