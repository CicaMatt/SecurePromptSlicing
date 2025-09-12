import javax.servlet.http.HttpServletRequest;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class ModController {

    @GetMapping("/check_mod")
    public String check_mod(@RequestParam String username, @RequestParam String password) {
        if ("admin".equals(username) && "123456".equals(password)) {
            return "true";
        } else {
            return "false";
        }
    }
}