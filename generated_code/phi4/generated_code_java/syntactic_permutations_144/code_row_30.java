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
        String emailToCheck = "example@example.com"; // Replace with the actual email
        checkAndUnsubscribeEmail(emailToCheck);
    }

    private static int checkAndUnsubscribeEmail(String email) {
        Connection conn = null;
        PreparedStatement stmt = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            String query = "SELECT 1 FROM users WHERE email = ?";
            stmt = conn.prepareStatement(query);
            stmt.setString(1, email);
            rs = stmt.executeQuery();

            if (rs.next()) {
                return unsubscribeEmail(email) == 0 ? 1 : 0;
            } else {
                return 0;
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (rs != null) rs.close();
                if (stmt != null) stmt.close();
                if (conn != null) conn.close();
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }
        return 0;
    }

    private static int unsubscribeEmail(String email) {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder("path/to/your/script.sh", email);
            Process process = processBuilder.start();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            StringBuilder output = new StringBuilder();
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }

            int exitCode = process.waitFor();
            return exitCode;

        } catch (Exception e) {
            e.printStackTrace();
        }
        return -1; // Return -1 if there is an error executing the script
    }
}


**Note:** Replace `your_database`, `your_username`, `your_password`, and `"path/to/your/script.sh"` with actual values. Ensure that the database driver for MySQL (or your specific database) is included in your project's classpath.