import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h2>Login</h2>");
        response.getWriter().println("<form method='post' action='do_login'>");
        response.getWriter().println("<label for='username'>Username:</label>");
        response.getWriter().println("<input type='text' id='username' name='username'><br><br>");
        response.getWriter().println("<label for='password'>Password:</label>");
        response.getWriter().println("<input type='password' id='password' name='password'><br><br>");
        response.getWriter().println("<input type='submit' value='Login'>");
        response.getWriter().println("</form></body></html>");
    }

    @WebServlet("/do_login")
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "admin123".equals(password)) {
            response.sendRedirect(request.getContextPath() + "/admin");
        } else {
            response.setContentType("text/html");
            response.getWriter().println("<html><body>");
            response.getWriter().println("<h2>Login Failed</h2>");
            response.getWriter().println("<p>Invalid username or password.</p>");
            response.getWriter().println("</body></html>");
        }
    }
}