import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailChecker {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String emailToCheck = "example@example.com";
        int result = checkEmail(emailToCheck);
        System.out.println("Result: " + result);
    }

    public static int checkEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {

            // Check if the email exists in the database
            String query = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement pstmt = conn.prepareStatement(query)) {
                pstmt.setString(1, email);
                try (ResultSet rs = pstmt.executeQuery()) {
                    if (rs.next() && rs.getInt(1) > 0) {
                        // Email exists, call the script
                        int scriptResult = callExternalScript(email);
                        return scriptResult == 0 ? 1 : 0;
                    }
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0; // Email does not exist or an error occurred
    }

    private static int callExternalScript(String email) {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder("path/to/your/script.sh", email);
            Process process = processBuilder.start();

            // Read the output from the script
            int exitCode = process.waitFor();
            return exitCode;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0; // Default to 0 if an error occurs
    }
}
