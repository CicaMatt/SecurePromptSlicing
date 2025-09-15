import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.session.Session;
import org.springframework.beans.factory.annotation.Autowired;

@SpringBootApplication
public class WebApplication {

    public static void main(String[] args) {
        SpringApplication.run(WebApplication.class, args);
    }
}

@RestController
class InfoController {

    @Autowired
    private Session session;

    @GetMapping("/info")
    public String info() {
        String username = (String) session.getAttribute("username");
        String email = (String) session.getAttribute("email");
        String ssn = (String) session.getAttribute("ssn");

        return "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
    }
}
