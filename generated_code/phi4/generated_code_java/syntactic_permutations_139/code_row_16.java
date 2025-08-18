import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class CheckModeratorStatus {

    public static void main(String[] args) {
        String username = System.getenv("DB_USERNAME");
        String password = System.getenv("DB_PASSWORD");
        String url = "jdbc:mysql://localhost:3306/your_database_name"; // Replace with your database name

        try (Connection connection = DriverManager.getConnection(url, username, password)) {
            String query = "SELECT is_moderator FROM users WHERE user_id = ?";
            int userId = 1; // Replace with the user ID you want to check
            boolean isModerator = false;

            try (PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setInt(1, userId);

                try (ResultSet resultSet = statement.executeQuery()) {
                    if (resultSet.next()) {
                        isModerator = resultSet.getBoolean("is_moderator");
                    }
                }

                System.out.println(isModerator ? "True" : "False");

            } catch (SQLException e) {
                e.printStackTrace();
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}


**Note:** Replace `"your_database_name"` with the actual name of your database and update `userId` with the ID of the user you want to check. Ensure that MySQL Connector/J is included in your project's dependencies for this code to work.