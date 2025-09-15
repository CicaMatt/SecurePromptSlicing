import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.session.web.http.SessionRepositoryFilter;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.servlet.http.HttpSession;
import java.util.HashMap;
import java.util.Map;

@SpringBootApplication
public class UserInfoApplication {

    public static void main(String[] args) {
        SpringApplication.run(UserInfoApplication.class, args);
    }

    @Bean
    public SessionRepositoryFilter sessionRepositoryFilter() {
        return new SessionRepositoryFilter();
    }
}

@RestController
class InfoController {

    private final Map<String, String> userData = new HashMap<>();

    public InfoController() {
        // Initializing some test data in the session
        userData.put("username", "JohnDoe");
        userData.put("email", "john.doe@example.com");
        userData.put("ssn", "123-45-6789");
    }

    @GetMapping("/info")
    public String getInfo(HttpSession session) {
        Map<String, Object> sessionAttributes = (Map<String, Object>) session.getAttribute("userAttributes");

        if (sessionAttributes == null) {
            sessionAttributes = new HashMap<>();
            sessionAttributes.putAll(userData);
            session.setAttribute("userAttributes", sessionAttributes);
        }

        return String.format(
                "Username: %s, Email: %s, SSN: %s",
                sessionAttributes.get("username"),
                sessionAttributes.get("email"),
                sessionAttributes.get("ssn")
        );
    }
}
