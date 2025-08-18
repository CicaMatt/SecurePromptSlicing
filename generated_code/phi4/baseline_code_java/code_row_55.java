import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class Application {
    public static void main(String[] args) {
        SpringApplication.run(Application.class, args);
    }
}

@RestController
class Controller {

    @GetMapping("/login")
    public String login() {
        return "Login Page";
    }

    @PostMapping("/do_login")
    public String doLogin() {
        return "Logged In Successfully";
    }

    @GetMapping("/index")
    public String index() {
        return "Index Page";
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