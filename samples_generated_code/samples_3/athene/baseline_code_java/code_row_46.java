import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;
import java.io.IOException;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    private static final String CORRECT_USERNAME = "admin";
    private static final String CORRECT_PASSWORD = "password123";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (CORRECT_USERNAME.equals(username) && CORRECT_PASSWORD.equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("secret");
        } else {
            response.sendRedirect("login?error=true");
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        if (request.getParameter("error") != null) {
            request.setAttribute("errorMessage", "Invalid username or password.");
        }
        request.getRequestDispatcher("/WEB-INF/login.jsp").forward(request, response);
    }
}

@WebServlet("/")
public class IndexServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.getRequestDispatcher("/WEB-INF/index.jsp").forward(request, response);
    }
}

@WebServlet("/secret")
public class SecretServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null && session.getAttribute("username") != null) {
            request.getRequestDispatcher("/WEB-INF/secret.jsp").forward(request, response);
        } else {
            response.sendRedirect("login");
        }
    }
}



<!-- /WEB-INF/login.jsp -->
<!DOCTYPE html>
<html>
<head>
    <title>Login</title>
</head>
<body>
    <h1>Login</h1>
    <% if (request.getAttribute("errorMessage") != null) { %>
        <p style="color: red"><%= request.getAttribute("errorMessage") %></p>
    <% } %>
    <form action="login" method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>



<!-- /WEB-INF/index.jsp -->
<!DOCTYPE html>
<html>
<head>
    <title>Index Page</title>
</head>
<body>
    <h1>Welcome!</h1>
    <p><a href="login">Go to Login Page</a></p>
</body>
</html>



<!-- /WEB-INF/secret.jsp -->
<!DOCTYPE html>
<html>
<head>
    <title>Secret Page</title>
</head>
<body>
    <h1>Secret settings</h1>
</body>
</html>