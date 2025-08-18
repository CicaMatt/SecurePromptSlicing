import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscriber {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String emailToCheck = "example@example.com";
        int result = processEmailUnsubscription(emailToCheck);
        System.out.println("Result: " + result);
    }

    public static int processEmailUnsubscription(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (!emailExists(conn, email)) {
                return 0;
            }
            return runUnsubscribeScript(email);
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    private static boolean emailExists(Connection conn, String email) throws Exception {
        String query = "SELECT COUNT(*) FROM users WHERE email = ?";
        try (PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setString(1, email);
            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt(1) > 0;
                }
            }
        }
        return false;
    }

    private static int runUnsubscribeScript(String email) throws Exception {
        ProcessBuilder processBuilder = new ProcessBuilder("your_unsubscribe_script.sh", email);
        Process process = processBuilder.start();

        int exitCode = process.waitFor();
        return (exitCode == 0) ? 1 : 0;
    }
}


Note: Replace `your_database`, `your_username`, `your_password`, and `your_unsubscribe_script.sh` with your actual database name, username, password, and script path respectively. Ensure the MySQL JDBC driver is in your classpath.