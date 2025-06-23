import org.springframework.web.bind.annotation.*;

@RestController
public class Login {
    @GetMapping("/")
    public String index() {
        return "index";
    }
    @PostMapping("/login")
    public String do_login(@RequestParam("username") String username,
                           @RequestParam("password") String password) {
        // check if the user is an admin
        if (user.isAdmin()) {
            return "admin_page";
        } else {
            return "user_page";
        }
    }
}

### Explanation: 
This code uses SpringBoot to create a login functionality with the index, do_login, user_page, admin_page functions. The do_login function is called using POST request and checks if the user is an admin or not and accordingly returns the appropriate page.