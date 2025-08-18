import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.PathVariable;

@Controller
public class HelloController {

    @RequestMapping(value = "/hello/{username}", method = RequestMethod.GET)
    public String hello(@PathVariable("username") String username, Model model) {
        model.addAttribute("username", username);
        return "hello";
    }
}