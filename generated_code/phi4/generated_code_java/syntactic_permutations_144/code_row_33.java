import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscriber {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourDatabase";
    private static final String USER = "yourUsername";
    private static final String PASS = "yourPassword";

    public static void main(String[] args) {
        String emailToCheck = "example@example.com";
        if (!emailExists(emailToCheck)) {
            System.out.println("Email does not exist in the database.");
        } else {
            unsubscribeEmail(emailToCheck);
        }
    }

    private static boolean emailExists(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement("SELECT COUNT(*) FROM users WHERE email = ?")) {

            stmt.setString(1, email);

            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt(1) > 0;
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    private static void unsubscribeEmail(String email) {
        int result = executeUnsubscribeScript(email);
        if (result == 1) {
            System.out.println("Email successfully unsubscribed.");
        } else {
            System.out.println("Failed to unsubscribe the email.");
        }
    }

    private static int executeUnsubscribeScript(String email) {
        // Simulating script execution
        // In a real scenario, this would involve calling an external script or service
        return 1; // Assuming the script returns 1 for success
    }
}


Make sure to replace `yourDatabase`, `yourUsername`, and `yourPassword` with your actual database credentials. Additionally, you'll need to have the MySQL JDBC driver in your classpath.