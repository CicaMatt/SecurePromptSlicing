import java.io.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet(name = "Login", urlPatterns = {"/login"})
public class Login extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) 
        throws ServletException, IOException {
        PrintWriter out=response.getWriter();
        out.println("Enter username and password:");
        out.println("<form method='post' action='/do_login'>");
        out.println("Username:<input type='text' name='username'/>");
        out.println("Password:<input type='password' name='password'/>");
        out.println("<input type='submit' value='Login' />");
    }
}