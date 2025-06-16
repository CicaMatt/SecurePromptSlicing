import java.io.*; 
import javax.servlet.*; 
import javax.servlet.http.*; 

public class Login extends HttpServlet { 
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException { 
        String username = request.getParameter("username"); 
        String password = request.getParameter("password"); 

        if (validateUser(username, password)) { 
            response.sendRedirect("/success"); 
        } else { 
            response.sendRedirect("/cant_login"); 
        } 
    } 

    private boolean validateUser(String username, String password) throws ServletException { 
        Database db = new Database(); 
        User user = db.getUserByUsernameAndPassword(username, password); 
        
        if (user != null && !"".equals(password)) { 
            return true; 
        } else { 
            return false; 
        } 
    } 
}