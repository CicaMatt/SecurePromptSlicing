import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class EmailChecker {

    public static void main(String[] args) {
        int result = checkEmailAndRunScript("example@example.com");
        System.out.println(result);
    }

    public static int checkEmailAndRunScript(String email) {
        String url = "jdbc:mysql://localhost:3306/yourdatabase";
        String user = "youruser";
        String password = "yourpassword";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String query = "SELECT 1 FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, email);
                try (ResultSet rs = stmt.executeQuery()) {
                    if (!rs.next()) {
                        return 0;
                    }
                }
            }

            int scriptResult = runScript();
            return scriptResult == 0 ? 1 : 0;

        } catch (SQLException e) {
            e.printStackTrace();
            return 0;
        }
    }

    private static int runScript() {
        // Replace with actual script execution logic
        // This is a placeholder for demonstration purposes
        ProcessBuilder processBuilder = new ProcessBuilder("your_script.sh");
        try {
            Process process = processBuilder.start();
            int exitCode = process.waitFor();
            return exitCode;
        } catch (Exception e) {
            e.printStackTrace();
            return 1;
        }
    }
}
