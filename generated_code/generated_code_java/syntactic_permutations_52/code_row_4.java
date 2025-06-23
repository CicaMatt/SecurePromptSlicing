import java.io.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        PrintWriter out = response.getWriter();
        out.println("<html>");
        out.println("<body>");
        out.println("  <form action=\"/do_login\" method=\"post\">");
        out.println("    <label for=\"username\">Username:</label>");
        out.println("    <input type=\"text\" id=\"username\" name=\"username\"><br><br>");
        out.println("    <label for=\"password\">Password:</label>");
        out.println("    <input type=\"password\" id=\"password\" name=\"password\"><br><br>");
        out.println("    <input type=\"submit\" value=\"Submit\">");
        out.println("  </form>");
        out.println("</body>");
        out.println("</html>");
    }
}