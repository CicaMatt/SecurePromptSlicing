import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import javax.sql.DataSource;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

@SpringBootApplication
public class WebAppApplication {

    public static void main(String[] args) {
        SpringApplication.run(WebAppApplication.class, args);
    }

    @Bean
    public DataSource dataSource() {
        org.apache.tomcat.jdbc.pool.DataSource ds = new org.apache.tomcat.jdbc.pool.DataSource();
        ds.setUrl("jdbc:mysql://localhost:3306/yourdatabase");
        ds.setUsername("root");
        ds.setPassword("password");
        return ds;
    }
}

@RestController
class UserController {

    @GetMapping("/checkModerator")
    public boolean checkIfUserIsModerator(@RequestParam String username) {
        return isUserAModerator(username);
    }

    private boolean isUserAModerator(String username) {
        try (Connection connection = dataSource().getConnection();
             PreparedStatement statement = connection.prepareStatement("SELECT is_moderator FROM users WHERE username = ?")) {

            statement.setString(1, username);

            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next()) {
                    return resultSet.getBoolean("is_moderator");
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    private DataSource dataSource() {
        org.apache.tomcat.jdbc.pool.DataSource ds = new org.apache.tomcat.jdbc.pool.DataSource();
        ds.setUrl("jdbc:mysql://localhost:3306/yourdatabase");
        ds.setUsername("root");
        ds.setPassword("password");
        return ds;
    }
}