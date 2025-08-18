import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UsernameExistsChecker {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourDatabaseName";
    private static final String USER = "yourUsername";
    private static final String PASS = "yourPassword";

    public static boolean doesUsernameExist(String username) {
        String query = "SELECT 1 FROM users WHERE username = ?";
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(query)) {

            pstmt.setString(1, username);

            try (ResultSet rs = pstmt.executeQuery()) {
                return rs.next();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }

    public static void main(String[] args) {
        String usernameToCheck = "exampleUser";
        boolean exists = doesUsernameExist(usernameToCheck);
        System.out.println("Does the username exist? " + exists);
    }
}


Make sure to replace `yourDatabaseName`, `yourUsername`, and `yourPassword` with your actual database details. Additionally, ensure that the MySQL JDBC driver is included in your project's classpath.