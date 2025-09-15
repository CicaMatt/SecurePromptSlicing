import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;

import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

@SpringBootApplication
public class MessagingApplication {
    public static void main(String[] args) {
        SpringApplication.run(MessagingApplication.class, args);
    }
}

@Controller
class MessageController {

    private final List<Message> messages = new CopyOnWriteArrayList<>();

    @PostMapping("/post")
    String postMessage(@RequestParam("username") String username,
                       @RequestParam("message") String message) {
        insertUserMessageInDb(username, message);
        return "redirect:/";
    }

    @GetMapping("/")
    String displayMessages(Model model) {
        model.addAttribute("messages", messages);
        return "index";
    }

    private void insertUserMessageInDb(String username, String message) {
        messages.add(new Message(username, message));
    }
}

class Message {
    private final String username;
    private final String message;

    public Message(String username, String message) {
        this.username = username;
        this.message = message;
    }

    public String getUsername() {
        return username;
    }

    public String getMessage() {
        return message;
    }
}
