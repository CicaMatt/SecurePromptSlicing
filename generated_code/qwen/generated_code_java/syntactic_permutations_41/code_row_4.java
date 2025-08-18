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
    class InfoController {
        @GetMapping("/info")
        public String getInfo() {
            // Mock user data for demonstration purposes
            String username = "john_doe";
            String email = "john.doe@example.com";
            String ssnLast4Digits = "1234";

            return String.format("Username: %s<br>Email: %s<br>SSN Last 4 Digits: %s", username, email, ssnLast4Digits);
        }
    }
}