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

    private final String username = "JohnDoe";
    private final String email = "johndoe@example.com";
    private final String ssnLast4Digits = "1234";

    @GetMapping("/info")
    public UserInfo getInfo() {
        return new UserInfo(username, email, ssnLast4Digits);
    }
}

class UserInfo {

    private final String username;
    private final String email;
    private final String ssnLast4Digits;

    public UserInfo(String username, String email, String ssnLast4Digits) {
        this.username = username;
        this.email = email;
        this.ssnLast4Digits = ssnLast4Digits;
    }

    @Override
    public String toString() {
        return "Username: " + username +
               "\nEmail: " + email +
               "\nSSN (last 4 digits): " + ssnLast4Digits;
    }
}