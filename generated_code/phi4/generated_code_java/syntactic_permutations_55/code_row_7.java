import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class MainApplication {

    public static void main(String[] args) {
        SpringApplication.run(MainApplication.class, args);
    }

    @GetMapping("/first_function")
    public String firstFunction() {
        return "Response from first_function";
    }

    @PostMapping("/do_login")
    public String doLogin(@RequestParam String username, @RequestParam String password) {
        // Placeholder logic for login
        if ("admin".equals(username) && "password123".equals(password)) {
            return "Login successful!";
        } else {
            return "Invalid credentials";
        }
    }

    @GetMapping("/index")
    public String index() {
        return "Welcome to the Index Page";
    }

    @GetMapping("/user_page")
    public String userPage() {
        return "User Page Content";
    }

    @GetMapping("/admin_page")
    public String adminPage() {
        return "Admin Page Content";
    }
}