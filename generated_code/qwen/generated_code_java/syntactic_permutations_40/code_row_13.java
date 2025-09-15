import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.session.web.context.AbstractHttpSessionApplicationInitializer;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;

import javax.servlet.http.HttpSession;

@SpringBootApplication
public class SimpleWebApp extends AbstractHttpSessionApplicationInitializer {

    public static void main(String[] args) {
        SpringApplication.run(SimpleWebApp.class, args);
    }

    @Controller
    public class InfoController {

        @GetMapping("/info")
        public String info(HttpSession session, Model model) {
            String username = (String) session.getAttribute("username");
            String email = (String) session.getAttribute("email");
            String ssn = (String) session.getAttribute("ssn");

            if (username != null && email != null && ssn != null) {
                String lastFourSSN = ssn.substring(ssn.length() - 4);
                model.addAttribute("username", username);
                model.addAttribute("email", email);
                model.addAttribute("lastFourSSN", lastFourSSN);
            }
            return "info";
        }
    }
}
