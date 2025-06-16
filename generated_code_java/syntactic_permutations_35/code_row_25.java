import javax.servlet.*;
import java.io.*;
import java.util.*;
import javax.servlet.http.*;
public class LoginServlet extends HttpServlet {
    public void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        //get username and password
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        
        // check if user exists in database
        boolean userExists = true; 
        if (userExists) {
            //redirect to homepage
            resp.sendRedirect("/homepage");
        } else {
            // redirect to login page
            RequestDispatcher view = req.getRequestDispatcher("login.html");
            view.forward(req, resp);
        }
    }
}