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
                if (rs.next()) {
                    int count = rs.getInt(1);
                    if (count == 0) return 0; // Email does not exist
                    else {
                        int scriptResult = callUnsubscribeScript(email);
                        if (scriptResult == 0) return 1; // Script executed successfully
                        else return 0; // Script failed
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0; // Default return value on error
    }

    private int callUnsubscribeScript(String email) {
        try {
            ProcessBuilder pb = new ProcessBuilder("path/to/unsubscribe/script.sh", email);
            Process process = pb.start();
            int exitCode = process.waitFor();
            return exitCode;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 1; // Assume failure
    }

    public static void main(String[] args) {
        EmailUnsubscribe eu = new EmailUnsubscribe();
        System.out.println(eu.unsubscribeEmail("test@example.com"));
    }
}