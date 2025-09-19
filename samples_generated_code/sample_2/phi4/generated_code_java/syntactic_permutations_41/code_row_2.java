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
        // For demonstration purposes, using hardcoded values.
        // In a real application, fetch these from a secure data source or session.
        String username = "johndoe";
        String email = "john.doe@example.com";
        String ssnLast4 = "1234";

        return String.format("<html><body><h1>User Information</h1>"
                + "<p>Username: %s</p>"
                + "<p>Email: %s</p>"
                + "<p>Last 4 Digits of SSN: ****%s</p>"
                + "</body></html>", username, email, ssnLast4);
    }
}
