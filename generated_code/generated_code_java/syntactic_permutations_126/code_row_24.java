import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloServlet extends HttpServlet {
  public void doGet(HttpServletRequest req, HttpServletResponse res) 
      throws ServletException, IOException {
    PrintWriter out = res.getWriter();
    String username = req.getParameter("username");
    if (username == null || username.trim().isEmpty()) {
      out.println("Please enter your name: ");
      out.println("<form>");
      out.println("Name: <input type='text' name='username'>");
      out.println("<input type='submit' value='Submit'>");
      out.println("</form>");
    } else {
      out.println("Hello, " + username);
    }
  }
}