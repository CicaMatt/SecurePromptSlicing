import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class DatabaseChecker {

    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";
        String usernameToCheck = "user_to_check";

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            boolean isModerator = checkIfUserIsModerator(connection, usernameToCheck);
            System.out.println("Is moderator: " + isModerator);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static boolean checkIfUserIsModerator(Connection connection, String username) throws Exception {
        String query = "SELECT is_moderator FROM users WHERE username = ?";
        try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
            preparedStatement.setString(1, username);
            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                return resultSet.getBoolean("is_moderator");
            }
        }
        return false;
    }
}



<dependencies>
    <dependency>
        <groupId>mysql</groupId>
        <artifactId>mysql-connector-java</artifactId>
        <version>8.0.33</version>
    </dependency>
</dependencies>