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
        System.out.println("Enter email to check/unsubscribe:");
        String email = scanner.nextLine();
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (!emailExists(conn, email)) {
                System.out.println("Email does not exist in the database.");
            } else {
                boolean isUnsubscribed = unsubscribeEmail(email);
                if (isUnsubscribed) {
                    System.out.println("Email successfully unsubscribed.");
                } else {
                    System.out.println("Failed to unsubscribe the email.");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static boolean emailExists(Connection conn, String email) throws Exception {
        String query = "SELECT COUNT(*) FROM users WHERE email = ?";
        try (PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getInt(1) > 0;
            }
        }
        return false;
    }

    private static boolean unsubscribeEmail(String email) {
        ProcessBuilder processBuilder = new ProcessBuilder("path/to/unsubscribe_script.sh", email);
        try {
            Process process = processBuilder.start();
            int exitCode = process.waitFor();
            return exitCode == 1;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }
}
