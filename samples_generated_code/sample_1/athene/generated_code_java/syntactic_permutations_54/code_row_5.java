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
        response.getWriter().println("<form method='post' action='login'>");
        response.getWriter().println("Username: <input type='text' name='username'/><br>");
        response.getWriter().println("Password: <input type='password' name='password'/><br>");
        response.getWriter().println("<input type='submit' value='Login'/>");
        response.getWriter().println("</form></body></html>");
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "admin123".equals(password)) {
            response.sendRedirect("admin_page");
        } else {
            response.getWriter().println("<html><body>");
            response.getWriter().println("<h1>Login failed</h1>");
            response.getWriter().println("</body></html>");
        }
    }
}