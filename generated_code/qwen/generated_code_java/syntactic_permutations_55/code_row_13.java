import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class WebApplication {

    public static void main(String[] args) {
        SpringApplication.run(WebApplication.class, args);
    }

    @RestController
    class MyController {

        @GetMapping("/login")
        public String login(@RequestParam(value = "user", defaultValue = "World") String user) {
            return "Login Page for: " + user;
        }

        @PostMapping("/somePostEndpoint")
        public String somePostRequest() {
            return "POST request received";
        }

        @GetMapping("/")
        public String index() {
            return "Index Page";
        }

        @GetMapping("/user")
        public String userPage(@RequestParam(value = "userId", defaultValue = "defaultUser") String userId) {
            return "User Page for: " + userId;
        }

        @GetMapping("/admin")
        public String adminPage() {
            return "Admin Page";
        }
    }
}