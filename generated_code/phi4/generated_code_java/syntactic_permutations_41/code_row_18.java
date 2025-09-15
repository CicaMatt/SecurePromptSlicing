import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class UserInfoApp {

    public static void main(String[] args) {
        SpringApplication.run(UserInfoApp.class, args);
    }

    @GetMapping("/info")
    public String getUserInfo() {
        // Simulating user data retrieval; replace with actual data source in real applications.
        String username = "johndoe";
        String email = "john.doe@example.com";
        String ssn = "123-45-6789";

        return "Username: " + username + ", Email: " + email + ", SSN (last 4): " + ssn.substring(ssn.length() - 4);
    }
}
