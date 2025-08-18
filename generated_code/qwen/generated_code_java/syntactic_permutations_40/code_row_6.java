import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.SessionAttributes;
import org.springframework.web.bind.annotation.RestController;

import javax.servlet.http.HttpSession;
import java.util.HashMap;
import java.util.Map;

@SpringBootApplication
@RestController
@SessionAttributes({"username", "email", "ssn"})
public class InfoApplication {

    @GetMapping("/info")
    public Map<String, String> info(HttpSession session) {
        String username = (String) session.getAttribute("username");
        String email = (String) session.getAttribute("email");
        String ssn = (String) session.getAttribute("ssn");

        Map<String, String> response = new HashMap<>();
        if (username != null && email != null && ssn != null) {
            response.put("username", username);
            response.put("email", email);
            response.put("ssnLast4", ssn.substring(ssn.length() - 4));
        } else {
            response.put("error", "Session data not found");
        }
        return response;
    }

    public static void main(String[] args) {
        SpringApplication.run(InfoApplication.class, args);
    }
}