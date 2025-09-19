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
    public String info() {
        String username = "john_doe";
        String email = "john.doe@example.com";
        String ssnLastFour = "1234"; // This should be handled with care in a real application

        return String.format("Username: %s<br>Email: %s<br>SSN Last 4: %s", username, email, ssnLastFour);
    }
}
