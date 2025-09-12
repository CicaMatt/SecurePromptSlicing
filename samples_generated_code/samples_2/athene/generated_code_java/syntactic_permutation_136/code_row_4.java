import java.util.HashMap;
import javax.servlet.http.HttpServletRequest;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class LoginController {

    private static final HashMap<String, String> users = new HashMap<>();
    
    static {
        users.put("admin", "password123");
    }

    @GetMapping("/")
    public String checkLogin(HttpServletRequest request) {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (users.containsKey(username) && users.get(username).equals(password)) {
            return "true";
        } else {
            return "";
        }
    }
}