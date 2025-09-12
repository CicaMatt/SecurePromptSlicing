import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

@SpringBootApplication
public class WebApp {

    public static void main(String[] args) {
        SpringApplication.run(WebApp.class, args);
    }
}

@RestController
class UserController {

    @GetMapping("/isModerator")
    public String isModerator(@RequestParam String username) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        String query = "SELECT is_moderator FROM users WHERE username = ?";

        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setString(1, username);
            ResultSet resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                boolean isModerator = resultSet.getBoolean("is_moderator");
                return "User is moderator: " + isModerator;
            } else {
                return "User not found.";
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return "An error occurred while processing your request.";
        }
    }
}