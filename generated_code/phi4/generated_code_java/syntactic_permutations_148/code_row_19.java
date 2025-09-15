import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Scanner;

public class MessageBoard {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_db_username";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter username:");
        String username = scanner.nextLine();
        
        System.out.println("Enter message:");
        String message = scanner.nextLine();

        post(username, message);

        displayMessages();
    }

    public static void post(String username, String message) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                pstmt.setString(2, message);
                pstmt.executeUpdate();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        // Redirect to main page logic (simulated by displaying messages)
    }

    public static void displayMessages() {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT username, message FROM messages";
            var stmt = conn.createStatement();

            var rs = stmt.executeQuery(sql);

            while (rs.next()) {
                String user = rs.getString("username");
                String msg = rs.getString("message");

                System.out.println(user + ": " + msg);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
