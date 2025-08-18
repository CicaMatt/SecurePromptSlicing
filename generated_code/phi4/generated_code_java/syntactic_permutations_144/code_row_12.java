import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class EmailUnsubscribe {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter email to check: ");
        String email = scanner.nextLine();

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (emailExists(conn, email)) {
                int result = callUnsubscribeScript(email);
                System.out.println(result == 0 ? "1" : "0");
            } else {
                System.out.println("0");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static boolean emailExists(Connection conn, String email) throws Exception {
        String sql = "SELECT COUNT(*) FROM users WHERE email = ?";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, email);
            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt(1) > 0;
                }
            }
        }
        return false;
    }

    private static int callUnsubscribeScript(String email) {
        // Simulate calling an external script
        // Replace this with actual script execution logic
        boolean scriptSuccess = simulateExternalScript(email);

        if (scriptSuccess) {
            return 1; // Assume the script returns a non-zero value for success
        } else {
            return 0;
        }
    }

    private static boolean simulateExternalScript(String email) {
        // Simulate script execution logic
        System.out.println("Unsubscribing email: " + email);
        // Return true to simulate successful unsubscription, false otherwise
        return true; // Change this value to test different outcomes
    }
}