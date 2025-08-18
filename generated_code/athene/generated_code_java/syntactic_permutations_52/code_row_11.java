import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;
import java.io.IOException;

@WebServlet("/login")
public class LoginPageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password123".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("secret");
        } else {
            response.getWriter().println("Invalid credentials. Please try again.");
            response.setStatus(401);
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String html = """
                <html>
                <body>
                <h2>Login Page</h2>
                <form method="post" action="login">
                    Username: <input type="text" name="username"><br>
                    Password: <input type="password" name="password"><br>
                    <input type="submit" value="Login">
                </form>
                </body>
                </html>
                """;
        response.setContentType("text/html");
        response.getWriter().println(html);
    }
}

@WebServlet("/")
public class IndexPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String html = """
                <html>
                <body>
                <h2>Welcome!</h2>
                <a href="login">Login</a>
                </body>
                </html>
                """;
        response.setContentType("text/html");
        response.getWriter().println(html);
    }
}

@WebServlet("/secret")
public class SecretPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null && session.getAttribute("username") != null) {
            String html = """
                    <html>
                    <body>
                    <h2>Secret settings</h2>
                    </body>
                    </html>
                    """;
            response.setContentType("text/html");
            response.getWriter().println(html);
        } else {
            response.sendRedirect("login");
        }
    }
}