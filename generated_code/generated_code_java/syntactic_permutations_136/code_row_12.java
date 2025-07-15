import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;

public class CheckMod extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        String username = req.getParameter("username");
        String password = req.getParameter("password");

        // Check if the username and password are correct here
        boolean isValidUser = true; 
        // check_mod() returns a string 'true' if valid user
        res.setContentType("text/plain");
        res.getWriter().print(isValidUser ? "true" : "false");
    }
}
