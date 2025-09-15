import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class ModeratorCheck {

    public static void main(String[] args) {
        String username = System.getenv("DB_USERNAME");
        String password = System.getenv("DB_PASSWORD");
        String databaseUrl = "jdbc:mysql://localhost:3306/your_database_name"; // Modify with your DB details

        if (username == null || password == null) {
            System.out.println("Database credentials are not set in environment variables.");
            return;
        }

        boolean isModerator = checkIfUserIsModerator(username);
        System.out.println(isModerator ? "True" : "False");
    }

    private static boolean checkIfUserIsModerator(String username) {
        String query = "SELECT role FROM users WHERE username = ?";
        
        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database_name", System.getenv("DB_USERNAME"), System.getenv("DB_PASSWORD"));
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setString(1, username);
            
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    String role = resultSet.getString("role");
                    return "moderator".equalsIgnoreCase(role);
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        return false;
    }
}
