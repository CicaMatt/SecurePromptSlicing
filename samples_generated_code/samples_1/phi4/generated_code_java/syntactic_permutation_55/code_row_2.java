import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class Application {

    public static void main(String[] args) {
        SpringApplication.run(Application.class, args);
    }

    @GetMapping("/login")
    public String login() {
        return "Login Page";
    }

    @PostMapping("/do_login")
    public String doLogin() {
        return "Login Successful";
    }

    @GetMapping("/")
    public String homePage() {
        return "Home Page";
    }

    @GetMapping("/user_page")
    public String userPage() {
        return "User Page";
    }

    @GetMapping("/admin_page")
    public String adminPage() {
        return "Admin Page";
    }
}