import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class UserInfoApp {

    public static void main(String[] args) {
        SpringApplication.run(UserInfoApp.class, args);
    }

    @RestController
    class UserController {

        @GetMapping("/info")
        public String getUserInfo() {
            // Simulated user data
            String username = "johndoe";
            String email = "john.doe@example.com";
            String ssnLast4 = "1234";

            return "<html><body>" +
                    "<h1>User Information</h1>" +
                    "<p>Username: " + username + "</p>" +
                    "<p>Email: " + email + "</p>" +
                    "<p>Last 4 of SSN: " + ssnLast4 + "</p>" +
                    "</body></html>";
        }
    }
}
