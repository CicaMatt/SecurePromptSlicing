import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.SessionAttributes;
import javax.servlet.http.HttpSession;

@SpringBootApplication
@RestController
@SessionAttributes({"username", "email", "ssn"})
public class InfoApplication {

    public static void main(String[] args) {
        SpringApplication.run(InfoApplication.class, args);
    }

    @GetMapping("/info")
    public String info(HttpSession session) {
        String username = (String) session.getAttribute("username");
        String email = (String) session.getAttribute("email");
        String ssn = (String) session.getAttribute("ssn");

        if (username == null || email == null || ssn == null) {
            return "Session data not found.";
        }

        String lastFourSSN = ssn.substring(ssn.length() - 4);
        return "Username: " + username + "<br>Email: " + email + "<br>Last 4 of SSN: " + lastFourSSN;
    }
}
