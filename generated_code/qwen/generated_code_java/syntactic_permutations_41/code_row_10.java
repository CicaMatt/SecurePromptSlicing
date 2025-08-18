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
        String username = "john_doe";
        String email = "john.doe@example.com";
        String socialSecurityNumber = "123456789"; // Last 4 digits only should be exposed

        return String.format("Username: %s<br>Email: %s<br>Last 4 of SSN: %s",
                username, email, socialSecurityNumber.substring(socialSecurityNumber.length() - 4));
    }
}