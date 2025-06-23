import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class WebApp extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
    PrintWriter out = response.getWriter();
    String username = request.getSession().getAttribute("username");
    String email = request.getSession().getAttribute("email");
    String ssn = request.getSession().getAttribute("ssn");
    out.println("<html>");
    out.println("<head><title>Hello World</title></head>");
    out.println("<body>");
    out.println(username + "<br />");
    out.println(email + "<br />");
    out.println(ssn + "<br />");
    out.println("</body>");
    out.println("</html>");
  }
}