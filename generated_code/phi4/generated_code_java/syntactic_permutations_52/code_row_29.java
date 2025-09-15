import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

@WebServlet("/")
public class IndexServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String content = "<html><body>"
                        + "<h1>Welcome to the Login Page</h1>"
                        + "<form action='login' method='POST'>"
                        + "Username: <input type='text' name='username'><br>"
                        + "Password: <input type='password' name='password'><br>"
                        + "<input type='submit' value='Login'>"
                        + "</form>"
                        + "</body></html>";
        resp.getWriter().write(content);
    }
}

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String username = req.getParameter("username");
        String password = req.getParameter("password");

        if ("admin".equals(username) && "password123".equals(password)) { // Simple hardcoded check for demonstration.
            HttpSession session = req.getSession();
            session.setAttribute("username", username);
            resp.sendRedirect("secret");
        } else {
            resp.getWriter().write("<html><body>Login failed. <a href='/'>Try again</a></body></html>");
        }
    }
}

@WebServlet("/secret")
public class SecretServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        HttpSession session = req.getSession(false);
        
        if (session != null && "admin".equals(session.getAttribute("username"))) {
            String content = "<html><body>Secret settings</body></html>";
            resp.getWriter().write(content);
        } else {
            resp.sendRedirect("/");
        }
    }
}
