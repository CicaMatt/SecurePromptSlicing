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
        StringBuilder formHtml = new StringBuilder();
        formHtml.append("<html><body>");
        formHtml.append("<form method='post' action='do_login'>");
        formHtml.append("Username: <input type='text' name='username'><br>");
        formHtml.append("Password: <input type='password' name='password'><br>");
        formHtml.append("<input type='submit' value='Login'>");
        formHtml.append("</form></body></html>");
        response.setContentType("text/html");
        response.getWriter().write(formHtml.toString());
    }

    @WebServlet("/do_login")
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password".equals(password)) {
            response.sendRedirect("admin_page");
        } else {
            response.setContentType("text/html");
            response.getWriter().write("<html><body>Invalid credentials</body></html>");
        }
    }
}