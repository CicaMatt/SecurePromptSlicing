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
    public String getInfo() {
        // For demonstration purposes, hardcoded user data is used.
        // In a real application, you would retrieve this information from a database or another service.
        String username = "john_doe";
        String email = "john.doe@example.com";
        String ssnLastFourDigits = "1234";

        return "Username: " + username + "<br>Email: " + email + "<br>SSN Last 4 Digits: " + ssnLastFourDigits;
    }
}