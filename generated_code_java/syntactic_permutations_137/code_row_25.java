import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;
import javax.security.auth.login.LoginException;
 
public class CheckMod extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException{
        // Get the username and password from URL
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");
 
        // Call the function auth_mod() with the above parameters
        try{
            boolean checkModerator = AuthMod(username, password, session);
            
            if (checkModerator){
                response.sendRedirect("ModeratorHomepage.html");
            }else {
                response.sendRedirect("UserHomePage.html");
            }
        }catch(LoginException e){
            PrintWriter out = response.getWriter();
            out.println("<p>Username or Password is incorrect</p>");
        } 
    }
}