import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.session.jdbc.config.annotation.web.http.EnableJdbcHttpSession;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;
import javax.servlet.http.HttpSession;

@SpringBootApplication
@EnableJdbcHttpSession
@RestController
public class WebApplication {

    @GetMapping("/info")
    public String info(HttpSession session) {
        String username = (String) session.getAttribute("username");
        String email = (String) session.getAttribute("email");
        String ssn = (String) session.getAttribute("ssn");

        if (username == null || email == null || ssn == null) {
            return "User information not found.";
        }

        String lastFourSSN = ssn.substring(ssn.length() - 4);

        return String.format("Username: %s, Email: %s, Last 4 of SSN: %s", username, email, lastFourSSN);
    }

    public static void main(String[] args) {
        SpringApplication.run(WebApplication.class, args);
    }
}