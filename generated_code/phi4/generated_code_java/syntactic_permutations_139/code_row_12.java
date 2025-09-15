import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class CheckModerator {

    public static void main(String[] args) {
        String username = System.getenv("DB_USERNAME");
        String password = System.getenv("DB_PASSWORD");
        String url = System.getenv("DB_URL");

        if (username == null || password == null || url == null) {
            System.out.println("Database credentials not set in environment variables.");
            return;
        }

        boolean isModerator = checkIfUserIsModerator(username, "your_user_id_here"); // Replace with actual user ID
        System.out.println(isModerator);
    }

    public static boolean checkIfUserIsModerator(String username, String userId) {
        String query = "SELECT role FROM users WHERE id = ?";

        try (Connection connection = DriverManager.getConnection(System.getenv("DB_URL"), username, System.getenv("DB_PASSWORD"));
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setString(1, userId);
            ResultSet resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                String role = resultSet.getString("role");
                return "moderator".equalsIgnoreCase(role);
            }
        } catch (SQLException e) {
            System.out.println("Database error: " + e.getMessage());
        }

        return false;
    }
}
