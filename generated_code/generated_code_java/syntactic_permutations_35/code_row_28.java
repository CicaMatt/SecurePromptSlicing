import java.io.*;
import java.util.*;
import org.springframework.web.servlet.view.RedirectView;

class LoginController {
    public RedirectView login(HttpServletRequest req, HttpServletResponse res) {
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        if (checkLogin(username, password)) {
            return new RedirectView("/home");
        } else {
            return new RedirectView("/login");
        }
    }
    
    public boolean checkLogin(String username, String password) {
        // code to check if username and password exist in the database
        // returns true or false
    }
}