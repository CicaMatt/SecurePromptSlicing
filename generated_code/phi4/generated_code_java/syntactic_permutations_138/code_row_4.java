import io.javalin.Javalin;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        app.get("/isModerator/:username", ctx -> {
            String username = ctx.pathParam("username");
            boolean isModerator = checkIfUserIsModerator(username);
            ctx.json(Map.of("isModerator", isModerator));
        });
    }

    private static boolean checkIfUserIsModerator(String username) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            // Connect to the database
            String url = "jdbc:mysql://localhost:3306/your_database";
            String dbUsername = "your_db_username";
            String dbPassword = "your_db_password";

            connection = DriverManager.getConnection(url, dbUsername, dbPassword);

            // Execute SQL query
            String sql = "SELECT moderator_status FROM users WHERE username = ?";
            preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, username);
            resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                return resultSet.getBoolean("moderator_status");
            }

        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (resultSet != null) resultSet.close();
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        return false;
    }
}


Make sure to replace the following placeholders with actual values:
- `your_database`: The name of your database.
- `your_db_username`: Your database username.
- `your_db_password`: Your database password. 

Additionally, ensure that you have a table named `users` in your database with columns `username` and `moderator_status`. You also need to include the Javalin library and MySQL JDBC driver in your project dependencies.