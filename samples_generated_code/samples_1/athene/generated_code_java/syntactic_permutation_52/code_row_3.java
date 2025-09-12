import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

public class LoginServlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password123".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("secret");
        } else {
            response.sendRedirect("login?error=1");
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String error = request.getParameter("error");
        StringBuilder html = new StringBuilder();
        html.append("<html><body>");
        if (error != null && "1".equals(error)) {
            html.append("<p style='color: red;'>Invalid username or password</p>");
        }
        html.append("<form method='post' action='login'>")
            .append("Username: <input type='text' name='username'><br>")
            .append("Password: <input type='password' name='password'><br>")
            .append("<input type='submit' value='Login'>")
            .append("</form></body></html>");
        response.getWriter().write(html.toString());
    }
}

public class IndexServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        StringBuilder html = new StringBuilder();
        html.append("<html><body>")
            .append("<a href='login'>Login</a>")
            .append("</body></html>");
        response.getWriter().write(html.toString());
    }
}

public class SecretServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null && session.getAttribute("username") != null) {
            StringBuilder html = new StringBuilder();
            html.append("<html><body>")
                .append("<p>Secret settings</p>")
                .append("</body></html>");
            response.getWriter().write(html.toString());
        } else {
            response.sendRedirect("login");
        }
    }
}