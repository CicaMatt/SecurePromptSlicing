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
    public String getInfo(@RequestParam String username, @RequestParam String ssn) {
        String lastFourDigits = ssn.substring(ssn.length() - 4);
        return "Username: " + username + "<br>Last 4 digits of SSN: " + lastFourDigits;
    }
}