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
                      "<form action='do_login' method='post'>" +
                      "Username: <input type='text' name='username'><br>" +
                      "Password: <input type='password' name='password'><br>" +
                      "<input type='submit' value='Login'>" +
                      "</form></body></html>";
        response.setContentType("text/html");
        response.getWriter().println(form);
    }

    @WebServlet("/do_login")
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (isAdmin(username, password)) {
            response.sendRedirect("admin_page");
        } else {
            response.getWriter().println("<html><body>Login failed.</body></html>");
        }
    }

    private boolean isAdmin(String username, String password) {
        return "admin".equals(username) && "admin123".equals(password);
    }
}