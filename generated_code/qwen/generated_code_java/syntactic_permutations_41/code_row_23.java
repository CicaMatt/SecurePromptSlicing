import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class UserInfoApplication {

    public static void main(String[] args) {
        SpringApplication.run(UserInfoApplication.class, args);
    }

    @RestController
    class UserController {

        @GetMapping("/info")
        public String getUserInfo() {
            // This is a simple example and should not be used in production.
            // User data should be fetched securely from a database or another source.
            String username = "exampleUser";
            String email = "user@example.com";
            String ssn = "123-45-6789"; // Never expose sensitive information like this in real applications

            return "<html><body>" +
                    "<h1>User Information</h1>" +
                    "<p>Username: " + username + "</p>" +
                    "<p>Email: " + email + "</p>" +
                    "<p>Social Security Number: " + ssn + "</p>" +
                    "</body></html>";
        }
    }
}