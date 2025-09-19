import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;

@SpringBootApplication
public class WebApplication {

    public static void main(String[] args) {
        SpringApplication.run(WebApplication.class, args);
    }
}

@Controller
class InfoController {

    @GetMapping("/info")
    public String getUserInfo(Model model) {
        // Dummy data for demonstration purposes
        model.addAttribute("username", "JohnDoe");
        model.addAttribute("email", "john.doe@example.com");
        model.addAttribute("socialSecurityNumber", "123-45-6789");

        return "info";
    }
}
