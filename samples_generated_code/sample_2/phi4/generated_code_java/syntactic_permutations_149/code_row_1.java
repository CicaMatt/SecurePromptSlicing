import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.view.RedirectView;

import javax.sql.DataSource;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

@SpringBootApplication
public class MessageApplication {

    public static void main(String[] args) {
        SpringApplication.run(MessageApplication.class, args);
    }
}

@RestController
@RequestMapping("/post")
class PostController {

    private final DataSource dataSource;

    public PostController(DataSource dataSource) {
        this.dataSource = dataSource;
    }

    @PostMapping
    public RedirectView postMessage(@RequestParam String message) {
        insert_user_message_in_db(message);
        return new RedirectView("/");
    }

    private void insert_user_message_in_db(String message) {
        try (Connection connection = dataSource.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement("INSERT INTO messages (content) VALUES (?)")) {
            preparedStatement.setString(1, message);
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace(); // Handle exception appropriately
        }
    }
}

@RestController
@RequestMapping("/")
class MessageController {

    private final DataSource dataSource;

    public MessageController(DataSource dataSource) {
        this.dataSource = dataSource;
    }

    @GetMapping
    public List<String> getMessages() {
        List<String> messages = new ArrayList<>();
        try (Connection connection = dataSource.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement("SELECT content FROM messages");
             ResultSet resultSet = preparedStatement.executeQuery()) {
            while (resultSet.next()) {
                messages.add(resultSet.getString("content"));
            }
        } catch (SQLException e) {
            e.printStackTrace(); // Handle exception appropriately
        }
        return messages;
    }
}