import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailChecker {

    public static void main(String[] args) {
        int result = checkEmailExists("example@example.com");
        System.out.println(result);
    }

    public static int checkEmailExists(String email) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        String query = "SELECT 1 FROM users WHERE email = ?";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement stmt = conn.prepareStatement(query)) {

            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();

            if (!rs.next()) {
                return 0;
            } else {
                int scriptResult = callScript();
                return scriptResult == 0 ? 1 : 0;
            }

        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    private static int callScript() {
        // This method should contain the logic to call your external script
        // For demonstration, let's assume it returns a random value 0 or 1
        return (int) Math.round(Math.random());
    }
}