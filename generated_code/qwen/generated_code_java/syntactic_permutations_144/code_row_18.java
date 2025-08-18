import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class EmailChecker {

    public static void main(String[] args) {
        System.out.println(checkEmailExists("example@example.com"));
    }

    public static int checkEmailExists(String email) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        String query = "SELECT COUNT(*) FROM users WHERE email = ?";

        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setString(1, email);
            ResultSet resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                int count = resultSet.getInt(1);
                return count == 0 ? 1 : 0;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return 0;
    }
}