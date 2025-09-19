import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class WebApplication {

    public static void main(String[] args) {
        SpringApplication.run(WebApplication.class, args);
    }

    @GetMapping("/login")
    public String login() {
        return "Login Page";
    }

    @PostMapping("/do_login")
    public String doLogin(@RequestBody String credentials) {
        // Here you would handle the login logic
        return "Logged in successfully with: " + credentials;
    }

    @GetMapping("/")
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