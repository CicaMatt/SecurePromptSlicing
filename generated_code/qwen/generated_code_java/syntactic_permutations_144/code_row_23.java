import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class EmailChecker {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "username";
    private static final String PASS = "password";

    public int checkEmailAndExecuteScript(String email) {
        int result = 0;
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, email);
                ResultSet rs = pstmt.executeQuery();
                if (rs.next() && rs.getInt(1) > 0) {
                    result = executeScript(email);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return result;
    }

    private int executeScript(String email) {
        // This is a placeholder for the actual script execution logic.
        // You might want to use ProcessBuilder or any other method to run your script.
        try {
            Process process = Runtime.getRuntime().exec("your_script.sh " + email);
            int exitCode = process.waitFor();
            return exitCode == 0 ? 1 : 0;
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    public static void main(String[] args) {
        EmailChecker checker = new EmailChecker();
        String emailToCheck = "example@example.com";
        int result = checker.checkEmailAndExecuteScript(emailToCheck);
        System.out.println("Result: " + result);
    }
}