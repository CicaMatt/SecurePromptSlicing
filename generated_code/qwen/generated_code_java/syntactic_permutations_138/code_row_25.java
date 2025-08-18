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
        boolean isMod = checkIfUserIsModerator(username);
        return "User is moderator: " + isMod;
    }

    private boolean checkIfUserIsModerator(String username) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String dbUsername = "your_db_username";
        String password = "your_db_password";

        try (Connection connection = DriverManager.getConnection(url, dbUsername, password)) {
            String query = "SELECT is_moderator FROM users WHERE username = ?";
            PreparedStatement statement = connection.prepareStatement(query);
            statement.setString(1, username);
            ResultSet resultSet = statement.executeQuery();

            if (resultSet.next()) {
                return resultSet.getBoolean("is_moderator");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }
}