import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class EmailChecker {

    public static void main(String[] args) {
        int result = checkEmailExists("test@example.com");
        System.out.println(result);
    }

    public static int checkEmailExists(String email) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String query = "SELECT 1 FROM users WHERE email = ?";
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1, email);

            ResultSet rs = stmt.executeQuery();
            if (!rs.next()) {
                return 0;
            }
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }

        int scriptResult = runScript();
        return scriptResult == 0 ? 1 : 0;
    }

    private static int runScript() {
        try {
            Process process = Runtime.getRuntime().exec("your_script.sh");
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            return process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
            return 1;
        }
    }
}