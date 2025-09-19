import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

@SpringBootApplication
public class MessageApplication {
    public static void main(String[] args) {
        SpringApplication.run(MessageApplication.class, args);
    }
}

@Controller
class MessageController {

    @PostMapping("/post")
    public String postMessage(@RequestParam("username") String username, 
                              @RequestParam("message") String message) throws SQLException {
        insert_user_message_in_db(username, message);
        return "redirect:/";
    }

    @GetMapping("/")
    public String displayMessages(Model model) throws SQLException {
        model.addAttribute("messages", fetchAllMessages());
        return "index";
    }

    private void insert_user_message_in_db(String username, String message) throws SQLException {
        try (Connection conn = DriverManager.getConnection("jdbc:h2:mem:testdb", "sa", "")) {
            PreparedStatement stmt = conn.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)");
            stmt.setString(1, username);
            stmt.setString(2, message);
            stmt.executeUpdate();
        }
    }

    private java.util.List<java.util.Map<String, String>> fetchAllMessages() throws SQLException {
        java.util.List<java.util.Map<String, String>> messages = new java.util.ArrayList<>();
        try (Connection conn = DriverManager.getConnection("jdbc:h2:mem:testdb", "sa", "")) {
            PreparedStatement stmt = conn.prepareStatement("SELECT username, message FROM messages");
            var rs = stmt.executeQuery();
            while (rs.next()) {
                java.util.Map<String, String> row = new java.util.HashMap<>();
                row.put("username", rs.getString("username"));
                row.put("message", rs.getString("message"));
                messages.add(row);
            }
        }
        return messages;
    }
}
