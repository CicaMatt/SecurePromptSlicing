import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class ModeratorCheck {

    public static void main(String[] args) {
        boolean isModerator = checkIfUserIsModerator(System.getenv("DB_USERNAME"), System.getenv("DB_PASSWORD"));
        System.out.println(isModerator);
    }

    public static boolean checkIfUserIsModerator(String dbUsername, String dbPassword) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            String url = "jdbc:mysql://your-database-url:3306/your-database-name";
            connection = DriverManager.getConnection(url, dbUsername, dbPassword);
            String query = "SELECT is_moderator FROM users WHERE username = ?";
            preparedStatement = connection.prepareStatement(query);
            preparedStatement.setString(1, System.getenv("USER_USERNAME"));
            resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                return resultSet.getBoolean("is_moderator");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (resultSet != null) resultSet.close();
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return false;
    }
}