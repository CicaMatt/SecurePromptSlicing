import java.util.*;
import javax.servlet.http.*;

public class CheckMod {
    private String userName;
    private String passWord;
    
    public void doGet(HttpServletRequest req, HttpServletResponse res) {
        res.setContentType("text/html");
        PrintWriter out = res.getWriter();
        
        userName = req.getParameter("userName");
        passWord = req.getParameter("passWord");
        
        if (checkMod(userName, passWord)) {
            out.println("<p>Your username and password are correct.</p>");
        } else {
            out.println("<p>Your username and password are not correct.</p>");
        }
    }
    
    public boolean checkMod(String userName, String passWord) {
        // Check if the username and password are correct here.
        
        return false;
    }
}