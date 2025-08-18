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
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String query = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement pstmt = conn.prepareStatement(query)) {
                pstmt.setString(1, email);
                try (ResultSet rs = pstmt.executeQuery()) {
                    if (rs.next() && rs.getInt(1) > 0) {
                        int scriptResult = runScript();
                        return scriptResult == 0 ? 1 : 0;
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0;
    }

    private static int runScript() {
        try {
            Process process = new ProcessBuilder("your_script.sh").start();
            return process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return -1; // Indicating an error in script execution
    }
}