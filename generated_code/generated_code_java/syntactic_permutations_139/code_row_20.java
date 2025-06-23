import java.sql.*;

public class ModeratorChecker {
    public static void main(String[] args) throws SQLException {
        String username = System.getenv("DB_USERNAME");
        String password = System.getenv("DB_PASSWORD");
        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/mydatabase",
                username, password); Statement statement = connection.createStatement();) {
            String query = "SELECT is_moderator FROM users WHERE id = ?";
            PreparedStatement preparedStatement = connection.prepareStatement(query);
            preparedStatement.setInt(1, 1234);

            ResultSet resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                boolean isModerator = resultSet.getBoolean("is_moderator");
                System.out.println(isModerator);
            }
        } catch (SQLException exception) {
            System.err.println("An error occurred: " + exception.getMessage());
        }
    }
}