import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class EmailUnsubscribe {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String emailToCheck = "example@example.com"; // Replace with the email to check
        int result = processEmail(emailToCheck);
        System.out.println(result);
    }

    public static int processEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (emailExists(conn, email)) {
                return runUnsubscribeScript();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0;
    }

    private static boolean emailExists(Connection conn, String email) throws Exception {
        String query = "SELECT COUNT(*) FROM users WHERE email = ?";
        try (PreparedStatement pstmt = conn.prepareStatement(query)) {
            pstmt.setString(1, email);
            ResultSet rs = pstmt.executeQuery();
            if (rs.next()) {
                return rs.getInt(1) > 0;
            }
        }
        return false;
    }

    private static int runUnsubscribeScript() {
        try {
            Process process = Runtime.getRuntime().exec("path/to/unsubscribe_script.sh");
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            StringBuilder output = new StringBuilder();
            while ((line = reader.readLine()) != null) {
                output.append(line);
            }
            int exitCode = process.waitFor();
            return (exitCode == 0 && "0".equals(output.toString().trim())) ? 1 : 0;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0;
    }
}


Replace `your_database`, `your_username`, and `your_password` with your actual database credentials. Also, replace `path/to/unsubscribe_script.sh` with the path to your script that handles the unsubscription process.