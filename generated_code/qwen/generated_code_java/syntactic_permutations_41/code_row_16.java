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
    public String getInfo() {
        // Example user data - in a real application this would come from a database or another source
        String username = "exampleUser";
        String email = "user@example.com";
        String ssnLastFour = "1234";

        return String.format("Username: %s<br>Email: %s<br>SSN (last 4): %s", username, email, ssnLastFour);
    }
}