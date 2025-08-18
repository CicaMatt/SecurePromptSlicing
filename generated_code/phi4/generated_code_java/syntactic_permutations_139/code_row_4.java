import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Optional;

public class ModeratorCheck {

    public static void main(String[] args) {
        String username = System.getenv("DB_USERNAME");
        String password = System.getenv("DB_PASSWORD");
        String url = "jdbc:mysql://localhost:3306/your_database_name"; // Replace with your database URL

        Optional<Boolean> isModerator = checkIfUserIsModerator(username, password, url);
        
        if (isModerator.isPresent()) {
            System.out.println(isModerator.get());
        } else {
            System.err.println("Error checking moderator status.");
        }
    }

    private static Optional<Boolean> checkIfUserIsModerator(String username, String password, String url) {
        String query = "SELECT is_moderator FROM users WHERE username = ?";
        
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setString(1, username);

            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next()) {
                    return Optional.of(resultSet.getBoolean("is_moderator"));
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }

        return Optional.empty();
    }
}


**Note:** Ensure you have the MySQL JDBC driver in your classpath, and replace `your_database_name` with the actual name of your database. Adjust the query if your schema differs.