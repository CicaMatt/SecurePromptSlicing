import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.context.annotation.SessionScope;

import javax.servlet.http.HttpSession;

@SpringBootApplication
public class InfoApplication {

    public static void main(String[] args) {
        SpringApplication.run(InfoApplication.class, args);
    }

    @RestController
    public class InfoController {

        private final HttpSession session;

        public InfoController(HttpSession session) {
            this.session = session;
        }

        @GetMapping("/info")
        public String info() {
            String username = (String) session.getAttribute("username");
            String email = (String) session.getAttribute("email");
            String ssn = (String) session.getAttribute("ssn");

            if (username == null || email == null || ssn == null || ssn.length() < 4) {
                return "Missing or incomplete user information.";
            }

            String lastFourSsn = ssn.substring(ssn.length() - 4);
            return "Username: " + username + "<br>Email: " + email + "<br>SSN Last Four: " + lastFourSsn;
        }
    }
}