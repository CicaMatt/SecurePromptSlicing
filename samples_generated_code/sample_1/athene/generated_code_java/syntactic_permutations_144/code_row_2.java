import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscribe {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    public int checkAndUnsubscribeEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String query = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement ps = conn.prepareStatement(query)) {
                ps.setString(1, email);
                try (ResultSet rs = ps.executeQuery()) {
                    if (rs.next() && rs.getInt(1) == 0) {
                        return 0;
                    }
                }
            }

            unsubscribeEmail(email);

            return 1;

        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    private void unsubscribeEmail(String email) {
        // Call your script here to unsubscribe the email
        // For example, using Runtime.exec or ProcessBuilder to execute a shell script:
        try {
            Process process = Runtime.getRuntime().exec("your_script.sh " + email);
            process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        EmailUnsubscribe eu = new EmailUnsubscribe();
        String email = "test@example.com";
        int result = eu.checkAndUnsubscribeEmail(email);
        System.out.println("Result: " + result);
    }
}