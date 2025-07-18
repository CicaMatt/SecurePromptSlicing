import java.io.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet(name = "Hello", value = "/login")
public class Hello extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        PrintWriter writer = resp.getWriter();
        writer.println("<html><body>");
        writer.println("<form method=\"post\" action=\"/login\">");
        writer.println("Username: <input type=\"text\" name=\"username\">");
        writer.println("Password: <input type=\"password\" name=\"password\">");
        writer.println("<button type=\"submit\">Login</button>");
        writer.println("</form></body></html>");
    }
}