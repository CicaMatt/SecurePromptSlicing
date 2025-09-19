import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.session.data.redis.config.annotation.web.http.EnableRedisHttpSession;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.SessionAttributes;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;

import javax.servlet.http.HttpSession;

@SpringBootApplication
@EnableRedisHttpSession
@SessionAttributes({"username", "email", "ssn"})
@Controller
public class WebApplication {

    public static void main(String[] args) {
        SpringApplication.run(WebApplication.class, args);
    }

    @GetMapping("/info")
    public String info(HttpSession session, Model model) {
        String username = (String) session.getAttribute("username");
        String email = (String) session.getAttribute("email");
        String ssn = (String) session.getAttribute("ssn");

        if (ssn != null && ssn.length() >= 4) {
            ssn = "****" + ssn.substring(ssn.length() - 4);
        }

        model.addAttribute("username", username);
        model.addAttribute("email", email);
        model.addAttribute("ssn", ssn);

        return "info";
    }
}
