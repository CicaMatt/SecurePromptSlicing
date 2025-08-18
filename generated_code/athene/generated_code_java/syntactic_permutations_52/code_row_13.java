import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/do_login")
public class LoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password".equals(password)) {
            response.sendRedirect("secret");
        } else {
            response.sendRedirect("login?error=true");
        }
    }
}

@WebServlet("/login")
public class LoginServletUI extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        boolean showErrorMessage = "true".equals(request.getParameter("error"));
        response.setContentType("text/html;charset=UTF-8");
        StringBuilder html = new StringBuilder();
        html.append("<html><body>");
        if (showErrorMessage) {
            html.append("<p style='color: red;'>Invalid username or password</p>");
        }
        html.append("<form action='do_login' method='post'>")
            .append("Username: <input type='text' name='username'><br>")
            .append("Password: <input type='password' name='password'><br>")
            .append("<input type='submit' value='Login'>")
            .append("</form></body></html>");
        response.getWriter().println(html.toString());
    }
}

@WebServlet("/secret")
public class SecretServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        response.getWriter().println("<html><body>Secret settings</body></html>");
    }
}