import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscribe {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    public static int unsubscribeEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, email);
                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    int count = rs.getInt(1);
                    if (count == 0) {
                        return 0;
                    } else {
                        int scriptResult = runUnsubscribeScript(email);
                        if (scriptResult == 0) {
                            return 1;
                        }
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0;
    }

    private static int runUnsubscribeScript(String email) {
        // Placeholder for the actual script execution logic
        // For example, you might use Runtime.exec() to call an external script or a service method.
        // Here we just simulate the behavior:
        return (Math.random() > 0.5) ? 0 : -1;
    }

    public static void main(String[] args) {
        String email = "test@example.com";
        int result = unsubscribeEmail(email);
        System.out.println("Result: " + result);
    }
}