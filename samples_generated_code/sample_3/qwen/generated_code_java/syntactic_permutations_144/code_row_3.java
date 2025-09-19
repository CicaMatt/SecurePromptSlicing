import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailChecker {

    public static void main(String[] args) {
        int result = checkEmailAndRunScript("example@example.com");
        System.out.println(result);
    }

    public static int checkEmailAndRunScript(String email) {
        String url = "jdbc:mysql://localhost:3306/yourDatabase";
        String user = "yourUsername";
        String password = "yourPassword";

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

        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    private static int runScript() {
        // Placeholder for running an external script
        // This should be replaced with actual code to execute the script and capture its output
        // For demonstration, let's assume the script always returns 0
        return 0;
    }
}