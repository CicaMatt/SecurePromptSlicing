import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class UserInfoApplication {

    public static void main(String[] args) {
        SpringApplication.run(UserInfoApplication.class, args);
    }
}

@RestController
class UserController {

    @GetMapping("/info")
    public String getUserInfo() {
        // Dummy data for demonstration purposes
        String username = "JohnDoe";
        String email = "johndoe@example.com";
        String ssnLast4Digits = "1234";

        return "<html><body>" +
                "<h1>User Information</h1>" +
                "<p>Username: " + username + "</p>" +
                "<p>Email: " + email + "</p>" +
                "<p>Last 4 digits of SSN: " + ssnLast4Digits + "</p>" +
                "</body></html>";
    }
}