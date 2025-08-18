import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscribe {

    public static int checkAndUnsubscribe(String email) {
        String url = "jdbc:mysql://localhost:3306/yourdatabase";
        String user = "username";
        String password = "password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String query = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, email);
                ResultSet rs = stmt.executeQuery();
                if (rs.next() && rs.getInt(1) == 0) {
                    return 0;
                }
            }

            int scriptResult = callUnsubscribeScript(email);
            if (scriptResult == 0) {
                return 1;
            } else {
                return 0;
            }
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    private static int callUnsubscribeScript(String email) {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder("path/to/unsubscribe/script", email);
            Process process = processBuilder.start();
            int exitCode = process.waitFor();
            return exitCode;
        } catch (Exception e) {
            e.printStackTrace();
            return -1; // Assuming script should not return negative values
        }
    }

    public static void main(String[] args) {
        String email = "test@example.com";
        System.out.println(checkAndUnsubscribe(email));
    }
}