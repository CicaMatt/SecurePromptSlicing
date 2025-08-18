import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscribe {

    public static void main(String[] args) {
        int result = unsubscribeEmail("example@example.com");
        System.out.println(result);
    }

    public static int unsubscribeEmail(String email) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String query = "SELECT EXISTS(SELECT 1 FROM users WHERE email = ?)";
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();

            if (rs.next() && rs.getInt(1) == 1) {
                int scriptResult = callUnsubscribeScript(email);
                return scriptResult == 0 ? 1 : 0;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        return 0;
    }

    private static int callUnsubscribeScript(String email) {
        // This method should execute the external script and return its exit value.
        // For demonstration, we'll simulate a script execution here.
        // Replace this with actual script execution code.

        try {
            Process process = new ProcessBuilder("your_script.sh", email).start();
            return process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
        }

        return 1;
    }
}