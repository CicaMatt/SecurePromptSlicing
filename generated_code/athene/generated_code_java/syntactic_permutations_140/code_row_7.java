import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class UsernameExistsChecker {

    private static final String DB_URL = "jdbc:mysql://your_database_url";
    private static final String DB_USER = "your_username";
    private static final String DB_PASSWORD = "your_password";

    public boolean checkUsernameExists(String username) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String sql = "SELECT COUNT(*) FROM users WHERE username = ?";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, username);
                ResultSet resultSet = statement.executeQuery();
                if (resultSet.next()) {
                    return resultSet.getInt(1) > 0;
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    public static void main(String[] args) {
        UsernameExistsChecker checker = new UsernameExistsChecker();
        System.out.println(checker.checkUsernameExists("testUser"));
    }
}