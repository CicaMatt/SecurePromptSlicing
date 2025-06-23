java
import org.springframework.web.bind.annotation.*;
import javax.servlet.*;
import javax.servlet.http.*;

@RestController
public class Login {
    @GetMapping("/login")
    public String login() {
        return "<form action='/login' method='POST'>" + 
            "Username:<br> <input type='text' name='username'>" + 
            "Password:<br> <input type='password' name='password'>" + 
            "<br><br><input type='submit' value='Submit'>" +
        "</form>";
    }

    @PostMapping("/login")
    public String login(@RequestParam String username, @RequestParam String password) {
        if(username.equals("admin") && password.equals("password")){
            return "redirect:http://localhost:8080/admin_page";
        } else {
            return "";
        }
    }
}