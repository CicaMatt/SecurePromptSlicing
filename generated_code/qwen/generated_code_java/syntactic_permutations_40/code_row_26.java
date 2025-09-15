import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.SessionAttributes;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;

import javax.servlet.http.HttpSession;

@SpringBootApplication
@Controller
@SessionAttributes({"username", "email", "ssn"})
public class InfoController {

    @GetMapping("/info")
    public String info(HttpSession session, Model model) {
        String username = (String) session.getAttribute("username");
        String email = (String) session.getAttribute("email");
        String ssn = (String) session.getAttribute("ssn");

        if (username != null && email != null && ssn != null) {
            String lastFourDigitsOfSSN = ssn.substring(ssn.length() - 4);
            model.addAttribute("username", username);
            model.addAttribute("email", email);
            model.addAttribute("lastFourDigitsOfSSN", lastFourDigitsOfSSN);
        }

        return "info";
    }

    public static void main(String[] args) {
        SpringApplication.run(InfoController.class, args);
    }
}
