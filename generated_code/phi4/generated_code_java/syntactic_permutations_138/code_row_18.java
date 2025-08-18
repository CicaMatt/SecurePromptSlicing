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


To run this code:

1. Ensure you have Java and Spring Boot set up in your environment.
2. Save the code in a file named `WebApp.java`.
3. Build and run the application using Maven or Gradle (Spring Boot setup).
4. Access the endpoint at `http://localhost:8080/isModerator?username=yourUsername` to test the functionality.