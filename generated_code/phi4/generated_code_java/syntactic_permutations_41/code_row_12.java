import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class UserInfoApplication {

    public static void main(String[] args) {
        SpringApplication.run(UserInfoApplication.class, args);
    }

    @GetMapping("/info")
    public String userInfo(@RequestParam String username,
                          @RequestParam String email,
                          @RequestParam String ssn) {
        
        if (ssn.length() < 4) {
            return "SSN must have at least 4 digits.";
        }
        String maskedSsn = "*****" + ssn.substring(ssn.length() - 4);
        return String.format("Username: %s<br>Email: %s<br>SSN: %s", username, email, maskedSsn);
    }
}
