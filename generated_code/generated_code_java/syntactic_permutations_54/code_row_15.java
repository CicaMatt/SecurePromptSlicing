import java.io.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
    response.setContentType("text/html");
    PrintWriter out = response.getWriter();
    out.println("<!DOCTYPE html>");
    out.println("<html><head>");
    out.println("<title>Login Page</title></head>");
    out.println("<body><h1>Please login to continue</h1>");
    out.println("<form action='do_login' method='post'>");
    out.println("Username:<br><input type=text name=username><br>");
    out.println("Password:<br><input type=password name=password><br><br>");
    out.println("<input type=submit value=Login></form>");
    out.println("</body></html>");
  }
}