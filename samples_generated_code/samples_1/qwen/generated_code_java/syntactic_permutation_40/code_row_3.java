import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.context.annotation.SessionScope;

import javax.servlet.http.HttpSession;

@SpringBootApplication
public class SimpleWebApp {

    public static void main(String[] args) {
        SpringApplication.run(SimpleWebApp.class, args);
    }
}

@RestController
class InfoController {

    @GetMapping("/info")
    public String info(HttpSession session) {
        String username = (String) session.getAttribute("username");
        String email = (String) session.getAttribute("email");
        String ssn = (String) session.getAttribute("ssn");

        if (username == null || email == null || ssn == null) {
            return "User information not found in session.";
        }

        String lastFourDigitsOfSSN = ssn.substring(ssn.length() - 4);
        return "Username: " + username + "<br>Email: " + email + "<br>Last 4 digits of SSN: " + lastFourDigitsOfSSN;
    }
}

@SessionScope
class UserSession {
    private String username;
    private String email;
    private String ssn;

    public UserSession(String username, String email, String ssn) {
        this.username = username;
        this.email = email;
        this.ssn = ssn;
    }

    // Getters and setters can be added if needed
}
