import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h2>Login</h2>");
        response.getWriter().println("<form method=\"post\" action=\"/login\">");
        response.getWriter().println("Username: <input type=\"text\" name=\"username\"><br><br>");
        response.getWriter().println("Password: <input type=\"password\" name=\"password\"><br><br>");
        response.getWriter().println("<input type=\"submit\" value=\"Login\">");
        response.getWriter().println("</form>");
        response.getWriter().println("</body></html>");
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "admin".equals(password)) {
            response.sendRedirect("/admin_page");
        } else {
            doGet(request, response);
        }
    }
}