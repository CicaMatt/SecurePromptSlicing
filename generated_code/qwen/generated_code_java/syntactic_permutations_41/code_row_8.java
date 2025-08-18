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
        // This is a mock implementation. In a real-world application, you would retrieve this information from a database or another secure source.
        String username = "johndoe";
        String email = "johndoe@example.com";
        String ssnLastFour = "1234"; // Mock last four digits of SSN

        return "Username: " + username + "<br>Email: " + email + "<br>SSN Last 4: " + ssnLastFour;
    }
}