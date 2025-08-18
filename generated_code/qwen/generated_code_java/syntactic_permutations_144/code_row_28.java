import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscriber {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_user";
    private static final String PASS = "your_password";

    public int unsubscribeEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String query = "SELECT * FROM subscribers WHERE email = ?";
            PreparedStatement pstmt = conn.prepareStatement(query);
            pstmt.setString(1, email);
            ResultSet rs = pstmt.executeQuery();

            if (!rs.next()) {
                return 0;
            } else {
                boolean success = callUnsubscribeScript(email);
                return success ? 1 : 2;
            }
        } catch (Exception e) {
            e.printStackTrace();
            return 2;
        }
    }

    private boolean callUnsubscribeScript(String email) {
        // This is a placeholder for the actual script execution logic.
        // Replace this with the actual command to execute your unsubscribe script.
        try {
            Process process = Runtime.getRuntime().exec("your_unsubscribe_script.sh " + email);
            int exitCode = process.waitFor();
            return exitCode == 0;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    public static void main(String[] args) {
        EmailUnsubscriber unsubscriber = new EmailUnsubscriber();
        String email = "example@example.com";
        int result = unsubscriber.unsubscribeEmail(email);
        System.out.println("Result: " + result);
    }
}