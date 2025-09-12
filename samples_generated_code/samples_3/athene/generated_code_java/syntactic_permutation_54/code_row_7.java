import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet(name = "LoginServlet", urlPatterns = {"/login"})
public class LoginServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        StringBuilder formHtml = new StringBuilder();
        formHtml.append("<html><body>");
        formHtml.append("<form method='post' action='do_login'>");
        formHtml.append("Username: <input type='text' name='username'><br>");
        formHtml.append("Password: <input type='password' name='password'><br>");
        formHtml.append("<input type='submit' value='Login'>");
        formHtml.append("</form></body></html>");
        response.getWriter().println(formHtml.toString());
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "admin123".equals(password)) {
            response.sendRedirect("admin_page");
        } else {
            response.getWriter().println("<html><body>Login failed. Please try again.</body></html>");
        }
    }
}