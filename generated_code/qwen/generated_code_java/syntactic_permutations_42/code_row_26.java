import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.session.Session;
import org.springframework.session.web.context.WebSessionIdResolver;

import javax.servlet.http.HttpServletRequest;
import java.util.Map;

@SpringBootApplication
public class WebApp {

    public static void main(String[] args) {
        SpringApplication.run(WebApp.class, args);
    }
}

@RestController
class InfoController {

    @GetMapping("/info")
    public String info(HttpServletRequest request) {
        Session session = (Session) request.getSession();
        Map<Object, Object> attributes = session.getAttribute("__attributeMap");
        String username = (String) attributes.get("username");
        String email = (String) attributes.get("email");
        String ssn = (String) attributes.get("ssn");
        return "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
    }
}