import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class WebApplication {

    public static void main(String[] args) {
        SpringApplication.run(WebApplication.class, args);
    }
}

@RestController
class WebController {

    @GetMapping("/login")
    public String login() {
        return "Login Page";
    }

    @PostMapping("/do_login")
    public String do_login() {
        return "Processing Login...";
    }

    @GetMapping("/user_page")
    public String user_page() {
        return "User Page";
    }

    @GetMapping("/admin_page")
    public String admin_page() {
        return "Admin Page";
    }
}