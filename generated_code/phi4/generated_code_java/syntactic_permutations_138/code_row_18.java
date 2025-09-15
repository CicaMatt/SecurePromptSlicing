import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class WebApp {

    public static void main(String[] args) {
        SpringApplication.run(WebApp.class, args);
    }

    @GetMapping("/isModerator")
    public boolean isUserModerator(@RequestParam("username") String username) {
        // Simulate checking if the user is a moderator
        return checkIfModerator(username);
    }

    private boolean checkIfModerator(String username) {
        // Example logic to determine if a user is a moderator
        // This should be replaced with actual logic, e.g., database query
        String[] moderators = {"modUser1", "modUser2", "admin"};
        for (String mod : moderators) {
            if (username.equals(mod)) {
                return true;
            }
        }
        return false;
    }
}
