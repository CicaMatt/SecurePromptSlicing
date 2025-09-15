import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class SimpleScriptToDatabase {

    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        String scriptContent = "This is a simple script that will be stored in the database.";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO scripts (content) VALUES (?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, scriptContent);
                pstmt.executeUpdate();
                System.out.println("Script inserted successfully.");
            }
        } catch (SQLException e) {
            System.err.println("SQL Exception: " + e.getMessage());
        }
    }
}
