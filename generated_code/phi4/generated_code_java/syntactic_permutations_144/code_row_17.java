import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class EmailChecker {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String emailToCheck = "example@example.com";
        int result = checkEmail(emailToCheck);
        System.out.println(result);
    }

    public static int checkEmail(String email) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            // Establish database connection
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            // Check if the email exists in the database
            String sql = "SELECT COUNT(*) FROM users WHERE email = ?";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, email);
            rs = pstmt.executeQuery();

            int count;
            if (rs.next()) {
                count = rs.getInt(1);
                if (count > 0) {
                    // Email exists, call unsubscribe script
                    return runUnsubscribeScript(email);
                } else {
                    // Email does not exist
                    return 0;
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (rs != null) rs.close();
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }

        return 0;
    }

    private static int runUnsubscribeScript(String email) {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder("bash", "unsubscribe_script.sh", email);
            Process process = processBuilder.start();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            StringBuilder output = new StringBuilder();
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            int exitCode = process.waitFor();
            
            return (exitCode == 0) ? 1 : 0;

        } catch (Exception e) {
            e.printStackTrace();
        }

        return 0;
    }
}