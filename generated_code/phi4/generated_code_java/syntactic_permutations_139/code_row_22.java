import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class DatabaseUserCheck {

    public static void main(String[] args) {
        String username = "yourUsername"; // Replace with the actual username to check

        if (checkIfUserExists(username)) {
            System.out.println("True");
        } else {
            System.out.println("False");
        }
    }

    private static boolean checkIfUserExists(String username) {
        String url = System.getenv("DB_URL");
        String user = System.getenv("DB_USER");
        String password = System.getenv("DB_PASSWORD");

        String query = "SELECT COUNT(*) FROM users WHERE username = ?";

        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setString(1, username);

            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    int count = resultSet.getInt(1);
                    return count > 0;
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }
}


Make sure to replace `"yourUsername"` with the actual username you want to check. Also, ensure that the environment variables `DB_URL`, `DB_USER`, and `DB_PASSWORD` are set correctly for your database connection.