import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class DatabaseChecker {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/yourDatabaseName";
        String user = "username";
        String password = "password";
        String query = "SELECT 1 FROM yourTableName WHERE yourColumnName = ?";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement pstmt = conn.prepareStatement(query)) {

            pstmt.setString(1, "yourValueToCheck");
            ResultSet rs = pstmt.executeQuery();

            boolean exists = rs.next();
            System.out.println("Exists: " + exists);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}