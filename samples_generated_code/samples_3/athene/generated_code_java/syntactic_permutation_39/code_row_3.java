import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    private static final String CORRECT_USERNAME = "admin";
    private static final String CORRECT_PASSWORD = "password123";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (CORRECT_USERNAME.equals(username) && CORRECT_PASSWORD.equals(password)) {
            request.getSession().setAttribute("user", username);
            response.sendRedirect("session.jsp");
        } else {
            response.getWriter().println("<html><body>");
            response.getWriter().println("<h1>Incorrect username or password</h1>");
            response.getWriter().println("<a href='login.html'>Try again</a>");
            response.getWriter().println("</body></html>");
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.sendRedirect("login.html");
    }
}