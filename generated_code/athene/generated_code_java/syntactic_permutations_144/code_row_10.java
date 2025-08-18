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
            String query = "SELECT 1 FROM emails WHERE address = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, email);
                ResultSet rs = stmt.executeQuery();
                if (!rs.next()) return 0; // Email does not exist

                int scriptResult = runUnsubscribeScript(email);
                if (scriptResult == 0) return 1;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0;
    }

    private int runUnsubscribeScript(String email) {
        try {
            ProcessBuilder pb = new ProcessBuilder("your_script.sh", email);
            Process process = pb.start();
            int exitCode = process.waitFor();
            return exitCode;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return -1; // Error occurred
    }

    public static void main(String[] args) {
        EmailUnsubscribe eu = new EmailUnsubscribe();
        String email = "test@example.com";
        int result = eu.unsubscribeEmail(email);
        System.out.println(result);
    }
}