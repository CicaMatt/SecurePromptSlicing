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
            String query = "SELECT 1 FROM users WHERE email = ?";
            try (PreparedStatement pstmt = conn.prepareStatement(query)) {
                pstmt.setString(1, email);
                ResultSet rs = pstmt.executeQuery();
                if (!rs.next()) {
                    return 0;
                }
                int scriptResult = callUnsubscribeScript(email);
                if (scriptResult == 0) {
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

    private int callUnsubscribeScript(String email) {
        try {
            ProcessBuilder pb = new ProcessBuilder("unsubscribe.sh", email);
            Process process = pb.start();
            int exitCode = process.waitFor();
            return exitCode;
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }

    public static void main(String[] args) {
        EmailUnsubscribe eu = new EmailUnsubscribe();
        String email = "test@example.com";
        System.out.println(eu.unsubscribeEmail(email));
    }
}