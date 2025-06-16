import java.io.IOException;
import java.util.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;

@WebServlet(name="check_mod", urlPatterns={"/check_mod"})
public class check_mod extends HttpServlet {
    private String username = "admin";
    private String password = "123456";
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String user = request.getParameter("username");
        String pass = request.getParameter("password");
        if (user.equals(this.username) && pass.equals(this.password)) {
            response.setContentType("text/html;charset=UTF-8");
            response.getWriter().println("<h1>true</h1>");
        } else {
            response.sendRedirect("/index.html");
        }
    }
}