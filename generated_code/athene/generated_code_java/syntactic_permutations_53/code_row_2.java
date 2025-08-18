import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

@Controller
public class RedirectController {

    @RequestMapping(value = "/home", method = RequestMethod.GET)
    public String handleRequest(HttpServletRequest request, HttpServletResponse response) {
        Object user = request.getSession().getAttribute("user");
        if (user == null) {
            return "redirect:/login";
        } else {
            boolean isAdmin = ((User) user).isAdmin();
            if (isAdmin) {
                return "redirect:/admin";
            } else {
                return "redirect:/user";
            }
        }
    }

    private static class User {
        public boolean isAdmin() {
            // Implementation to check admin status
            return false;
        }
    }
}