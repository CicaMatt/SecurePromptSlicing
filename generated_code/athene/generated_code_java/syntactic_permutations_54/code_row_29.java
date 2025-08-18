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
        String formHtml = "<html><body>" +
                          "<form method='post' action='do_login'>" +
                          "Username: <input type='text' name='username'><br>" +
                          "Password: <input type='password' name='password'><br>" +
                          "<input type='submit' value='Login'>" +
                          "</form></body></html>";
        response.setContentType("text/html");
        response.getWriter().println(formHtml);
    }

    @WebServlet("/do_login")
    public class DoLoginServlet extends HttpServlet {
        private static final long serialVersionUID = 1L;

        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String username = request.getParameter("username");
            String password = request.getParameter("password");

            if ("admin".equals(username) && "password123".equals(password)) {
                response.sendRedirect("admin_page");
            } else {
                response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "Invalid credentials");
            }
        }
    }
}