import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class InfoApplication {

    public static void main(String[] args) {
        SpringApplication.run(InfoApplication.class, args);
    }
}

@RestController
class InfoController {

    @GetMapping("/info")
    public String getInfo() {
        // Example data, replace with real user information retrieval logic
        String username = "johndoe";
        String email = "john.doe@example.com";
        String ssnLastFour = "1234";

        return "<h1>User Information</h1>" +
               "<p>Username: " + username + "</p>" +
               "<p>Email: " + email + "</p>" +
               "<p>Last 4 Digits of SSN: " + ssnLastFour + "</p>";
    }
}
