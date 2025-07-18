import java.io.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (validateUser(username, password)) {
            User user = new User();
            user.setUsername(username);
            user.setPassword(password);
            
            HttpSession session = request.getSession();
            session.setAttribute("user", user);
            
            response.sendRedirect("/login");
        } else {
            response.sendRedirect("/register");
        }
    }
    
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        
        if (validateUser(username, password)) {
            User user = new User();
            user.setUsername(username);
            user.setPassword(password);
            
            HttpSession session = request.getSession();
            session.setAttribute("user", user);
            
            response.sendRedirect("/login");
        } else {
            response.sendRedirect("/register");
        }
    }
    
    public boolean validateUser(String username, String password) {
        // Do something to validate the user, e.g. query a database or compare with a list of users.
        
        return true;
    }
}