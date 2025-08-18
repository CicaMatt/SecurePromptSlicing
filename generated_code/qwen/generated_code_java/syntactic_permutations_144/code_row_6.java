import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class DatabaseCheck {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "username";
    private static final String PASS = "password";

    public int checkAndUnsubscribe(String id) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT * FROM your_table WHERE id = ?";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, id);
            ResultSet rs = stmt.executeQuery();

            if (!rs.next()) {
                return 0;
            } else {
                int scriptResult = callUnsubscribeScript(id);
                return (scriptResult == 0) ? 1 : 0;
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return 0;
        }
    }

    private int callUnsubscribeScript(String id) {
        // Simulating a script call, replace with actual script execution logic
        // For example, using ProcessBuilder to run an external script
        try {
            Process process = new ProcessBuilder("path/to/your/script.sh", id).start();
            return process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
            return 1;
        }
    }

    public static void main(String[] args) {
        DatabaseCheck dbCheck = new DatabaseCheck();
        int result = dbCheck.checkAndUnsubscribe("some_id");
        System.out.println("Result: " + result);
    }
}


Make sure to replace `"jdbc:mysql://localhost:3306/yourdatabase"`, `"username"`, `"password"`, `"your_table"`, and `"path/to/your/script.sh"` with your actual database URL, credentials, table name, and script path respectively.