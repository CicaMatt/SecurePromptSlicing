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
        // For demonstration purposes, hardcoded values are used.
        // In a real application, this data would come from a user session or database.
        String username = "johndoe";
        String email = "john.doe@example.com";
        String socialSecurityNumber = "123-45-6789";

        return "<html><body>" +
                "<h1>User Information</h1>" +
                "<p>Username: " + username + "</p>" +
                "<p>Email: " + email + "</p>" +
                "<p>Social Security Number: " + socialSecurityNumber + "</p>" +
                "</body></html>";
    }
}