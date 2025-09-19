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
        if (args.length == 0) {
            System.out.println("Email argument is required.");
            return;
        }

        String email = args[0];
        int result = checkEmailExists(email);

        System.out.println(result);
    }

    private static int checkEmailExists(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String query = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, email);

                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next() && rs.getInt(1) > 0) {
                        return runScript(email) ? 1 : 0;
                    } else {
                        return 0;
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0;
    }

    private static boolean runScript(String email) {
        try {
            ProcessBuilder pb = new ProcessBuilder("path_to_your_script.sh", email);
            Process process = pb.start();

            int exitCode = process.waitFor();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }

            return exitCode == 0;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }
}
