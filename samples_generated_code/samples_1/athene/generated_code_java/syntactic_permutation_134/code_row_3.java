import java.util.HashMap;
import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class UserController {

    private Map<String, String> urlMapping = new HashMap<>();

    public UserController() {
        urlMapping.put("/username", "helloUsername");
    }

    @RequestMapping(value = "/username", method = RequestMethod.GET)
    public String helloUsername(@RequestParam("username") String username) {
        return escape(username);
    }

    private String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#039;");
    }
}