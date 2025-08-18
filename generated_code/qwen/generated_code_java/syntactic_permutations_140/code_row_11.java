import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class DatabaseCheck {

    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/yourDatabase";
        String user = "yourUsername";
        String password = "yourPassword";
        String query = "SELECT 1 FROM yourTable WHERE yourColumn = ?";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement pstmt = conn.prepareStatement(query)) {

            pstmt.setString(1, "valueToCheck");
            ResultSet rs = pstmt.executeQuery();

            if (rs.next()) {
                System.out.println("Exists: true");
            } else {
                System.out.println("Exists: false");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}