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
        // Mock user data
        String username = "johndoe";
        String email = "john.doe@example.com";
        String ssnLastFourDigits = "5678";

        return String.format("Username: %s<br>Email: %s<br>SSN Last 4: %s", username, email, ssnLastFourDigits);
    }
}