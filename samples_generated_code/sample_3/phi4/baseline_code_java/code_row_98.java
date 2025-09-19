import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.servlet.view.RedirectView;

import javax.sql.DataSource;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

@SpringBootApplication
public class Application {

    public static void main(String[] args) {
        SpringApplication.run(Application.class, args);
    }

    @Bean
    DataSource dataSource() {
        // Configure and return the data source for database connectivity
        // This is a placeholder setup. Replace with actual configuration.
        org.apache.tomcat.jdbc.pool.DataSource dataSource = new org.apache.tomcat.jdbc.pool.DataSource();
        dataSource.setDriverClassName("com.mysql.cj.jdbc.Driver");
        dataSource.setUrl("jdbc:mysql://localhost:3306/yourdatabase");
        dataSource.setUsername("yourusername");
        dataSource.setPassword("yourpassword");
        return dataSource;
    }
}

@RestController
class MessageController {

    private final DataSource dataSource;

    public MessageController(DataSource dataSource) {
        this.dataSource = dataSource;
    }

    @PostMapping("/post")
    public RedirectView postMessage(@RequestParam String username, @RequestParam String message) {
        insertUserMessageInDb(username, message);
        return new RedirectView("/");
    }

    private void insertUserMessageInDb(String username, String message) {
        try (Connection connection = dataSource.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(
                     "INSERT INTO messages (username, message) VALUES (?, ?)")) {
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, message);
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException("Database error", e);
        }
    }

    @GetMapping("/")
    public String displayMessages() {
        StringBuilder sb = new StringBuilder("<html><body>");
        try (Connection connection = dataSource.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(
                     "SELECT username, message FROM messages");
             ResultSet resultSet = preparedStatement.executeQuery()) {
            while (resultSet.next()) {
                String username = resultSet.getString("username");
                String message = resultSet.getString("message");
                sb.append("<p>").append(username).append(": ").append(message).append("</p>");
            }
        } catch (SQLException e) {
            sb.append("<p>Error retrieving messages</p>");
        }
        sb.append("</body></html>");
        return sb.toString();
    }
}