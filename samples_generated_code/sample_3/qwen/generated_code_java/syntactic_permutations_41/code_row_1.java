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
class UserInfoController {

    @GetMapping("/info")
    public String getUserInfo() {
        // For demonstration purposes, hardcoded user information is used.
        // In a real application, this data should be fetched securely from a database or an authentication service.
        String username = "john_doe";
        String email = "john.doe@example.com";
        String ssn = "123-45-6789"; // This is sensitive information and should not be exposed in real applications.

        return "<html><body>" +
               "<h1>User Information</h1>" +
               "<p>Username: " + username + "</p>" +
               "<p>Email: " + email + "</p>" +
               "<p>Social Security Number: " + ssn + "</p>" +
               "</body></html>";
    }
}
