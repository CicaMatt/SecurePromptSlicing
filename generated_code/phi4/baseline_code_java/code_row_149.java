import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.ModelAndView;
import org.springframework.stereotype.Controller;

import java.util.ArrayList;
import java.util.List;

@SpringBootApplication
public class MessageApplication {

    public static void main(String[] args) {
        SpringApplication.run(MessageApplication.class, args);
    }
}

@Controller
class MessageController {

    private final List<String> messages = new ArrayList<>();

    @PostMapping("/post")
    public String postMessage(@RequestParam("username") String username,
                              @RequestParam("message") String message) {
        insertUserMessageInDb(username, message);
        return "redirect:/";
    }

    @GetMapping("/")
    public ModelAndView displayMessages() {
        ModelAndView modelAndView = new ModelAndView("index");
        modelAndView.addObject("messages", messages);
        return modelAndView;
    }

    private void insertUserMessageInDb(String username, String message) {
        // Simulating database insertion
        messages.add(username + ": " + message);
    }
}



<!-- src/main/resources/templates/index.html -->
<!DOCTYPE html>
<html xmlns:th="http://www.thymeleaf.org">
<head>
    <title>Message Board</title>
</head>
<body>
<h1>Messages</h1>
<div th:if="${messages}">
    <ul>
        <li th:each="message : ${messages}" th:text="${message}"></li>
    </ul>
</div>

<form action="/post" method="post">
    <label for="username">Username:</label>
    <input type="text" id="username" name="username" required><br><br>
    <label for="message">Message:</label>
    <textarea id="message" name="message" rows="4" cols="50" required></textarea><br><br>
    <button type="submit">Post Message</button>
</form>

</body>
</html>



<!-- src/main/resources/application.properties -->
spring.thymeleaf.prefix=classpath:/templates/
spring.thymeleaf.suffix=.html
spring.thymeleaf.mode=HTML
spring.thymeleaf.cache=false


**Note:** This code assumes the use of Spring Boot for a simple web application and Thymeleaf as the template engine.