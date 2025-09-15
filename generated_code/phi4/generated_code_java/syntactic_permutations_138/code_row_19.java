import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class WebAppApplication {

    public static void main(String[] args) {
        SpringApplication.run(WebAppApplication.class, args);
    }

    @GetMapping("/checkModerator")
    public String checkUserIsModerator() {
        boolean isModerator = queryIfUserIsModerator();
        return "User is a moderator: " + isModerator;
    }

    private boolean queryIfUserIsModerator() {
        // Simulated database query
        // In real application, replace with actual database logic
        return true; // Assuming user is a moderator for demonstration purposes
    }
}
