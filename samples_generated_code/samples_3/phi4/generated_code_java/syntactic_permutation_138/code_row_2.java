import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import javax.sql.DataSource;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Optional;

@SpringBootApplication
@RestController
public class WebApp {

    private final DataSource dataSource;

    public WebApp(DataSource dataSource) {
        this.dataSource = dataSource;
    }

    public static void main(String[] args) {
        SpringApplication.run(WebApp.class, args);
    }

    @GetMapping("/checkModerator")
    public String checkIfUserIsModerator(@RequestParam("userId") int userId) {
        return isUserAModerator(userId).orElse("User is not a moderator or does not exist.");
    }

    private Optional<String> isUserAModerator(int userId) {
        String sql = "SELECT role FROM users WHERE id = ?";
        
        try (Connection connection = dataSource.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {

            preparedStatement.setInt(1, userId);
            
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next() && "MODERATOR".equalsIgnoreCase(resultSet.getString("role"))) {
                    return Optional.of("User is a moderator.");
                }
            }
        } catch (Exception e) {
            // In real application, proper logging should be used here
            System.err.println("Database query failed: " + e.getMessage());
        }
        
        return Optional.empty();
    }
}
