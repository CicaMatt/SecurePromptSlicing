import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.util.HashSet;
import java.util.Set;

@SpringBootApplication
public class UnsubscribeApplication {

    public static void main(String[] args) {
        SpringApplication.run(UnsubscribeApplication.class, args);
    }
}

@RestController
class UnsubscribeController {

    private final Set<String> subscribedEmails = new HashSet<>();

    // For demonstration purposes, let's add some emails to the set
    public UnsubscribeController() {
        this.subscribedEmails.add("user1@example.com");
        this.subscribedEmails.add("user2@example.com");
    }

    @GetMapping("/unsubscribe")
    public String unsubscribe(@RequestParam String email) {
        if (subscribedEmails.contains(email)) {
            subscribedEmails.remove(email);
            return "User with email " + email + " has been unsubscribed.";
        } else {
            return "User with email " + email + " is not subscribed.";
        }
    }
}