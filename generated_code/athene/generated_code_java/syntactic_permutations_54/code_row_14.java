import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<form method='post' action='/do_login'>");
        response.getWriter().println("<label for='username'>Username:</label>");
        response.getWriter().println("<input type='text' id='username' name='username'><br>");
        response.getWriter().println("<label for='password'>Password:</label>");
        response.getWriter().println("<input type='password' id='password' name='password'><br>");
        response.getWriter().println("<button type='submit'>Login</button>");
        response.getWriter().println("</form></body></html>");
    }
}

@WebServlet("/do_login")
public class DoLoginServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "admin123".equals(password)) {
            response.sendRedirect("/admin_page");
        } else {
            response.setContentType("text/html");
            response.getWriter().println("<html><body>");
            response.getWriter().println("<p>Login failed. Please try again.</p>");
            response.getWriter().println("</body></html>");
        }
    }
}