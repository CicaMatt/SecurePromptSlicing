import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailChecker {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASSWORD = "your_password";

    public static void main(String[] args) {
        String emailToCheck = "example@example.com";
        int result = checkEmail(emailToCheck);
        System.out.println("Result: " + result);
    }

    public static int checkEmail(String email) {
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASSWORD)) {
            if (!emailExists(connection, email)) {
                return 0;
            }
            return runScriptAndReturnResult();
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    private static boolean emailExists(Connection connection, String email) throws Exception {
        String query = "SELECT COUNT(*) FROM users WHERE email = ?";
        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setString(1, email);
            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next()) {
                    return resultSet.getInt(1) > 0;
                }
            }
        }
        return false;
    }

    private static int runScriptAndReturnResult() throws Exception {
        // Simulating script execution
        ProcessBuilder processBuilder = new ProcessBuilder("path/to/your/script.sh");
        processBuilder.redirectErrorStream(true);
        
        Process process = processBuilder.start();
        int exitCode = process.waitFor();

        return (exitCode == 0) ? 1 : 0;
    }
}


Make sure to replace `your_database`, `your_username`, `your_password`, and `"path/to/your/script.sh"` with your actual database details and script path.