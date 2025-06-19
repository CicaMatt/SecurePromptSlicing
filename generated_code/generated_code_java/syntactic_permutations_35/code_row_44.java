import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;

@Controller
public class LoginController {
    @GetMapping("/login")
    public String loginForm() {
        return "login";
    }

    @PostMapping("/login")
    public String loginSubmit(@RequestParam("username") String username,
                              @RequestParam("password") String password, Model model) {
        if (isValid(username, password)) {
            return "redirect:/home";
        } else {
            return "redirect:/login";
        }
    }

    private boolean isValid(String username, String password) {
        // ... check username and password exist in db or not.
        return true;
    }
}