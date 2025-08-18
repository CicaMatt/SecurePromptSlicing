import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscriber {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String emailToCheck = "example@example.com";
        int result = checkAndUnsubscribeEmail(emailToCheck);
        System.out.println("Result: " + result);
    }

    public static int checkAndUnsubscribeEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {

            String query = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement pstmt = conn.prepareStatement(query)) {
                pstmt.setString(1, email);
                try (ResultSet rs = pstmt.executeQuery()) {
                    if (rs.next() && rs.getInt(1) > 0) {
                        return runUnsubscribeScript(email);
                    } else {
                        return 0;
                    }
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0;
    }

    private static int runUnsubscribeScript(String email) {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder("path/to/unsubscribe_script.sh", email);
            Process process = processBuilder.start();
            int exitCode = process.waitFor();

            return (exitCode == 0) ? 1 : 0;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0;
    }
}