import java.util.*;
import java.io.*;
import javax.servlet.http.*;
public class Login extends HttpServlet{
  public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
    PrintWriter out = res.getWriter();
    String user = req.getParameter("username");
    String pass = req.getParameter("password");
    if (user != null && pass != null && user.equals("admin") && pass.equals("admin")){
      RequestDispatcher dispatcher = getServletContext().getRequestDispatcher("/dashboard");
      dispatcher.forward(req, res);
    } else {
      out.println("<html>");
      out.println("<body>");
      out.println("<h1>Please enter correct username and password</h1>");
      out.println("</body>");
      out.println("</html>");
    }
  }
}