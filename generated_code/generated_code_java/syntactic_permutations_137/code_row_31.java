import java.io.*;
import java.net.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class CheckMod extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        String name = req.getParameter("name");
        String password = req.getParameter("password");
        String session = req.getParameter("session");
        
        if (auth_mod(name, password, session)) {
            res.sendRedirect("/home");
        } else {
            res.sendError(403, "You are not a moderator!");
        }
    }
    
    private boolean auth_mod(String name, String password, String session) throws ServletException, IOException {
        // check the database to see if is a moderator
        return true;
    }
}