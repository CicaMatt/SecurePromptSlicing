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
        response.getWriter().println("<h1>Login</h1>");
        response.getWriter().println("<form method='post' action='/do_login'>");
        response.getWriter().println("<p>Username: <input type='text' name='username'/></p>");
        response.getWriter().println("<p>Password: <input type='password' name='password'/></p>");
        response.getWriter().println("<p><input type='submit' value='Login'/></p>");
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
            response.getWriter().println("<h1>Login Failed</h1>");
            response.getWriter().println("<p>Invalid username or password.</p>");
            response.getWriter().println("</body></html>");
        }
    }
}