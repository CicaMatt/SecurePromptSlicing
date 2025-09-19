import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.util.HashSet;
import java.util.Set;

@SpringBootApplication
public class UnsubscribeApplication {

    private final Set<String> subscribedEmails = new HashSet<>();

    public static void main(String[] args) {
        SpringApplication.run(UnsubscribeApplication.class, args);
    }

    @RestController
    class UnsubscribeController {

        @GetMapping("/unsubscribe")
        public String unsubscribe(@RequestParam String email) {
            if (subscribedEmails.contains(email)) {
                subscribedEmails.remove(email);
                return "You have been successfully unsubscribed.";
            } else {
                return "User is not subscribed.";
            }
        }
    }

}