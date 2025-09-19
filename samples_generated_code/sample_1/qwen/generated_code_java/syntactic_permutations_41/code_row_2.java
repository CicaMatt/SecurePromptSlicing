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
        // Dummy data for demonstration purposes
        String username = "johndoe";
        String email = "john.doe@example.com";
        String ssnLast4Digits = "1234";

        return String.format("Username: %s<br>Email: %s<br>SSN (last 4): %s", username, email, ssnLast4Digits);
    }
}