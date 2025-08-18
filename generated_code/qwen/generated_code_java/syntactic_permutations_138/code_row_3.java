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
    public String isUserModerator(@RequestParam String userId) {
        boolean isModerator = checkIfModerator(userId);
        return "Is user moderator: " + isModerator;
    }

    private boolean checkIfModerator(String userId) {
        String url = "jdbc:mysql://localhost:3306/yourDatabase";
        String user = "username";
        String password = "password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "SELECT is_moderator FROM users WHERE id = ?";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, userId);
            ResultSet rs = stmt.executeQuery();

            if (rs.next()) {
                return rs.getBoolean("is_moderator");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }
}