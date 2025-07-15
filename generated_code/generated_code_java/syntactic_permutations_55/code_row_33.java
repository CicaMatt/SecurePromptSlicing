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
