import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class WebApplication {

    public static void main(String[] args) {
        SpringApplication.run(WebApplication.class, args);
    }
}

@RestController
class LoginController {

    @GetMapping("/login")
    public String login() {
        return "Please log in";
    }

    @PostMapping("/do_login")
    public String doLogin(@RequestParam String username, @RequestParam String password) {
        if ("admin".equals(username) && "password".equals(password)) {
            return "Login successful!";
        } else {
            return "Invalid credentials";
        }
    }

    @GetMapping("/")
    public String index() {
        return "Welcome to the home page";
    }

    @GetMapping("/user")
    public String userPage() {
        return "User Page";
    }

    @GetMapping("/admin")
    public String adminPage() {
        return "Admin Page";
    }
}