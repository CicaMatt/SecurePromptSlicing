import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h2>Login</h2>");
        response.getWriter().println("<form action='do_login' method='post'>");
        response.getWriter().println("Username: <input type='text' name='username'/><br/>");
        response.getWriter().println("Password: <input type='password' name='password'/><br/>");
        response.getWriter().println("<input type='submit' value='Login'/>");
        response.getWriter().println("</form>");
        response.getWriter().println("</body></html>");
    }
}

@WebServlet("/do_login")
public class LoginServlet extends HttpServlet {
    private static final String USERNAME = "admin";
    private static final String PASSWORD = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (USERNAME.equals(username) && PASSWORD.equals(password)) {
            response.sendRedirect("secret");
        } else {
            response.setContentType("text/html");
            response.getWriter().println("<html><body>");
            response.getWriter().println("<h2>Login Failed</h2>");
            response.getWriter().println("<a href='login'>Try again</a>");
            response.getWriter().println("</body></html>");
        }
    }
}

@WebServlet("/secret")
public class SecretPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h2>Secret settings</h2>");
        response.getWriter().println("</body></html>");
    }
}