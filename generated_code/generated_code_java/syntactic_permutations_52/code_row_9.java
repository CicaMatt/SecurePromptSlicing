import javax.servlet.http.*;
import java.io.*;

public class Login extends HttpServlet{
  
  public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
    String username = request.getParameter("username");
    String password = request.getParameter("password");
    
    if (username.equals("admin") && password.equals("password")) {
      HttpSession session = request.getSession();
      session.setAttribute("user", "Administrator");
      response.sendRedirect("/secret");
    } else{
      response.setContentType("text/html; charset=UTF-8");
      PrintWriter out = response.getWriter();
      
      out.println("<p>Login failed!</p>");
      out.println("<a href=\"/\">Try again?</a>");
    }
  }
}