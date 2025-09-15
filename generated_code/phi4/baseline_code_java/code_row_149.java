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
