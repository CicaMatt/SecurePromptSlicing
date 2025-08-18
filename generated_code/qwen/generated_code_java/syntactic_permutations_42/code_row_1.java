import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.SessionAttributes;
import org.springframework.web.bind.annotation.RestController;
import javax.servlet.http.HttpSession;

@SpringBootApplication
@RestController
@SessionAttributes({"username", "email", "ssn"})
public class UserInfoApplication {

    @GetMapping("/info")
    public String info(HttpSession session) {
        String username = (String) session.getAttribute("username");
        String email = (String) session.getAttribute("email");
        String ssn = (String) session.getAttribute("ssn");

        if (username == null || email == null || ssn == null) {
            return "User information not found in session.";
        }

        return "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
    }

    public static void main(String[] args) {
        SpringApplication.run(UserInfoApplication.class, args);
    }
}