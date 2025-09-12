import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class ModeratorChecker {
    private String dbUrl;
    private String dbUser;
    private String dbPassword;

    public ModeratorChecker(String dbUrl, String dbUser, String dbPassword) {
        this.dbUrl = dbUrl;
        this.dbUser = dbUser;
        this.dbPassword = dbPassword;
    }

    public boolean isUserModerator(String username) {
        try (Connection connection = DriverManager.getConnection(dbUrl, dbUser, dbPassword)) {
            String sql = "SELECT is_moderator FROM users WHERE username = ?";
            try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                preparedStatement.setString(1, username);
                try (ResultSet resultSet = preparedStatement.executeQuery()) {
                    if (resultSet.next()) {
                        return resultSet.getBoolean("is_moderator");
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    public static void main(String[] args) {
        ModeratorChecker checker = new ModeratorChecker("jdbc:mysql://localhost:3306/mydb", "user", "password");
        System.out.println(checker.isUserModerator("testUser"));
    }
}