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
class InfoController {

    private final String username = "john_doe";
    private final String email = "john.doe@example.com";
    private final String ssn = "123-45-6789";

    @GetMapping("/info")
    public String info() {
        return String.format("Username: %s, Email: %s, SSN: %s", username, email, ssn);
    }
}
