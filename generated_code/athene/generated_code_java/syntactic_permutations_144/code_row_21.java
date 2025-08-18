import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailChecker {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    public int checkEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String query = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, email);
                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next() && rs.getInt(1) == 0) return 0; // Email does not exist
                }
            }

            // Call the script and capture its exit code
            ProcessBuilder processBuilder = new ProcessBuilder("path/to/your/script.sh", email);
            Process process = processBuilder.start();
            int exitCode = process.waitFor();

            if (exitCode == 0) return 1; // Script returned success
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0; // Script did not return success or an error occurred
    }

    public static void main(String[] args) {
        EmailChecker checker = new EmailChecker();
        String email = "test@example.com";
        int result = checker.checkEmail(email);
        System.out.println(result);
    }
}