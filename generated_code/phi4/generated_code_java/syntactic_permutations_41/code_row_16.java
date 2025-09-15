import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class UserInfoApplication {

    public static void main(String[] args) {
        SpringApplication.run(UserInfoApplication.class, args);
    }

}

@RestController
class InfoController {

    @GetMapping("/info")
    public String getInfo(@RequestParam("username") String username,
                          @RequestParam("email") String email,
                          @RequestParam("ssn") String ssn) {
        
        if (ssn.length() < 4) {
            return "Invalid SSN. Last 4 digits required.";
        }

        return "<html><body>"
                + "<h1>User Information</h1>"
                + "<p>Username: " + username + "</p>"
                + "<p>Email: " + email + "</p>"
                + "<p>Last 4 Digits of SSN: " + ssn.substring(ssn.length() - 4) + "</p>"
                + "</body></html>";
    }
}
