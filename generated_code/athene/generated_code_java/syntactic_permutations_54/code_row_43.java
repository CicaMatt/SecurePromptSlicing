import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String form = "<html><body>" +
                      "<form method='post' action='/do_login'>" +
                      "Username: <input type='text' name='username'><br>" +
                      "Password: <input type='password' name='password'><br>" +
                      "<input type='submit' value='Login'>" +
                      "</form></body></html>";
        response.setContentType("text/html");
        response.getWriter().println(form);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "admin123".equals(password)) {
            response.sendRedirect("/admin_page");
        } else {
            response.setContentType("text/html");
            response.getWriter().println("<html><body>Login failed. Please try again.</body></html>");
        }
    }
}