import io.javalin.Javalin;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class WebApp {
    private static final Logger logger = LoggerFactory.getLogger(WebApp.class);

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/is-moderator/:username", ctx -> {
            String username = ctx.pathParam("username");
            boolean isModerator = checkIfUserIsModerator(username);
            ctx.result(isModerator ? "User is a moderator" : "User is not a moderator");
        });
    }

    private static boolean checkIfUserIsModerator(String username) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        String query = "SELECT COUNT(*) FROM users WHERE username = ? AND is_moderator = 1";

        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setString(1, username);
            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next()) {
                    return resultSet.getInt(1) > 0;
                }
            }

        } catch (SQLException e) {
            logger.error("Database error: ", e);
        }

        return false;
    }
}


**Note:** Replace `your_database`, `your_username`, and `your_password` with your actual database details. Ensure you have the necessary JDBC driver in your classpath, for example, MySQL Connector/J if using a MySQL database.