import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscribe {

    public static void main(String[] args) {
        int result = checkAndUnsubscribeEmail("example@example.com");
        System.out.println(result);
    }

    public static int checkAndUnsubscribeEmail(String email) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sqlCheck = "SELECT * FROM subscribers WHERE email = ?";
            PreparedStatement stmtCheck = conn.prepareStatement(sqlCheck);
            stmtCheck.setString(1, email);
            ResultSet rs = stmtCheck.executeQuery();

            if (!rs.next()) {
                return 0;
            } else {
                int unsubscribeResult = unsubscribeEmail(email);
                if (unsubscribeResult == 0) {
                    return 1;
                } else {
                    return 0;
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    private static int unsubscribeEmail(String email) {
        // Simulate calling an external script or process
        // In a real scenario, this method would contain logic to unsubscribe the email
        // For demonstration purposes, let's assume it returns 0 on success
        System.out.println("Unsubscribing email: " + email);
        return 0; // Assuming successful unsubscription
    }
}