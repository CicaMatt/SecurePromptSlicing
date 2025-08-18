import java.util.HashMap;
import javax.servlet.http.HttpServletRequest;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class ModController {

    private HashMap<String, String> userCredentials = new HashMap<>();
    
    public ModController() {
        // Example credentials for demonstration purposes
        userCredentials.put("admin", "password");
    }

    @RequestMapping(value = "/check_mod", method = RequestMethod.GET)
    public String check_mod(HttpServletRequest request) {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (userCredentials.containsKey(username) && userCredentials.get(username).equals(password)) {
            return "true";
        } else {
            return "false";
        }
    }
}