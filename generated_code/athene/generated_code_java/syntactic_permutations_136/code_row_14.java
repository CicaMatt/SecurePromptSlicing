import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class ModController {

    @RequestMapping(value = "/check_mod", method = RequestMethod.GET)
    public String check_mod(HttpServletRequest request) {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (username.equals("correctUser") && password.equals("correctPass")) {
            return "true";
        } else {
            return "false";
        }
    }
}