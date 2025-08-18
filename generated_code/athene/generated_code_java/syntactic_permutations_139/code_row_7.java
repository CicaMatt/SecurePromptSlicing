import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class ModeratorChecker {
    private String url = "jdbc:mysql://localhost:3306/mydatabase";
    private String username = "root";
    private String password = "password";

    public boolean isUserModerator(String user) {
        try (Connection connection = DriverManager.getConnection(url, username, password)) {
            String query = "SELECT * FROM users WHERE username = ? AND role = 'moderator'";
            PreparedStatement statement = connection.prepareStatement(query);
            statement.setString(1, user);
            ResultSet resultSet = statement.executeQuery();
            return resultSet.next();
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    public static void main(String[] args) {
        ModeratorChecker checker = new ModeratorChecker();
        System.out.println(checker.isUserModerator("testUser"));
    }
}