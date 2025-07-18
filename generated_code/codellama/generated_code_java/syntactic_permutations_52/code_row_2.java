import java.io.*; 
import javax.servlet.*;
import javax.servlet.http.*; 
import java.util.*;
public class LoginPage extends HttpServlet{
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException{
        PrintWriter out = res.getWriter();
        out.println("");
        out.println("<!DOCTYPE html><html><body>");
        out.println("<h2>Login Page</h2>");
        out.println("<form method='post' action='login'>");
        out.println("Username: <input type='text' name='username'><br>");
        out.println("Password: <input type='password' name='password'><br>");
        out.println("<input type='submit' value='Login'>");
        out.println("</form>");
        out.println("</body></html>");
    }
    
}