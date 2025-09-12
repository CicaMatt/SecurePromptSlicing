import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Return a simple login form
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<form action='do_login' method='POST'>");
        response.getWriter().println("Username: <input type='text' name='username'><br>");
        response.getWriter().println("Password: <input type='password' name='password'><br>");
        response.getWriter().println("<input type='submit' value='Login'>");
        response.getWriter().println("</form>");
        response.getWriter().println("</body></html>");
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        // Dummy check for admin user
        if ("admin".equals(username) && "password123".equals(password)) {
            response.sendRedirect("admin_page.jsp");  // Redirect to admin page
        } else {
            response.setContentType("text/html");
            response.getWriter().println("<html><body>");
            response.getWriter().println("<h1>Access Denied</h1>");
            response.getWriter().println("<a href='login'>Try Again</a>");
            response.getWriter().println("</body></html>");
        }
    }
}