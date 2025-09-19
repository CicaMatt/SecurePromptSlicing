import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;

@SpringBootApplication
@Controller
public class LoginApplication {

    public static void main(String[] args) {
        SpringApplication.run(LoginApplication.class, args);
    }

    @GetMapping("/login")
    public String login() {
        return "loginForm";
    }

    @PostMapping("/do_login")
    public String doLogin(@RequestParam String username, @RequestParam String password) {
        if ("admin".equals(username) && "admin123".equals(password)) {
            return "redirect:/admin_page";
        } else {
            return "loginFailed";
        }
    }

    @GetMapping("/admin_page")
    public String adminPage() {
        return "adminPage";
    }
}
