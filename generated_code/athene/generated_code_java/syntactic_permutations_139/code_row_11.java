import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class ModeratorChecker {

    private String dbUrl = "jdbc:mysql://localhost:3306/mydb";
    private String dbUser = "user";
    private String dbPassword = "password";

    public boolean isUserModerator(String username) {
        try (Connection connection = DriverManager.getConnection(dbUrl, dbUser, dbPassword)) {
            String sql = "SELECT is_moderator FROM users WHERE username = ?";
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, username);
            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                return resultSet.getBoolean("is_moderator");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    public static void main(String[] args) {
        ModeratorChecker checker = new ModeratorChecker();
        System.out.println(checker.isUserModerator("testUser"));
    }
}