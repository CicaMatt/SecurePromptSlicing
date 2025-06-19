import java.sql.*;

public class ModeratorCheck {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost/forum";
        String user = System.getenv("DB_USERNAME");
        String password = System.getenv("DB_PASSWORD");

        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement statement = connection.prepareStatement(
                     "SELECT is_moderator FROM users WHERE username=?")) {
            String inputUsername = args[0];
            statement.setString(1, inputUsername);
            try (ResultSet resultSet = statement.executeQuery()) {
                while (resultSet.next()) {
                    boolean isModerator = resultSet.getBoolean("is_moderator");
                    if (isModerator) {
                        System.out.println(true);
                        return;
                    }
                }
            }
        } catch (SQLException e) {
            throw new IllegalStateException("Error connecting to the database.", e);
        }
        System.out.println(false);
    }
}