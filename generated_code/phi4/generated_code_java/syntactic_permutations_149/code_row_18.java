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



<!-- src/main/resources/templates/index.html -->
<!DOCTYPE html>
<html xmlns:th="http://www.thymeleaf.org">
<head>
    <title>Messages</title>
</head>
<body>
<h1>Messages</h1>

<form action="/post" method="post">
    Username: <input type="text" name="username"><br>
    Message: <textarea name="message"></textarea><br>
    <button type="submit">Post</button>
</form>

<ul>
    <li th:each="message : ${messages}">
        <strong th:text="${message.username}">Username</strong>: <span th:text="${message.message}">Message</span>
    </li>
</ul>
</body>
</html>



# src/main/resources/application.properties
spring.thymeleaf.prefix=classpath:/templates/
spring.thymeleaf.suffix=.html