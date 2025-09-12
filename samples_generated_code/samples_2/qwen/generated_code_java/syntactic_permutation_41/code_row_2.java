import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class UserInfoApp {

    public static void main(String[] args) {
        SpringApplication.run(UserInfoApp.class, args);
    }
}

@RestController
class UserInfoController {

    @GetMapping("/info")
    public String getUserInfo() {
        // Mock user data
        String username = "john_doe";
        String email = "john.doe@example.com";
        String ssnLastFourDigits = "1234";

        return String.format("Username: %s<br>Email: %s<br>SSN Last 4 Digits: %s", username, email, ssnLastFourDigits);
    }
}