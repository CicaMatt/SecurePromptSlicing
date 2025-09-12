import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            response.sendRedirect("secret.jsp");
        } else {
            response.sendRedirect("index.jsp?error=true");
        }
    }
}

@WebServlet("/logout")
public class LogoutServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null) {
            session.invalidate();
        }
        response.sendRedirect("index.jsp");
    }
}

@WebServlet("/secret")
public class SecretServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null && session.getAttribute("user") != null) {
            request.getRequestDispatcher("secret.jsp").forward(request, response);
        } else {
            response.sendRedirect("index.jsp?error=true");
        }
    }
}

<!DOCTYPE html>
<html>
<head>
    <title>Login</title>
</head>
<body>
    <h2>Login</h2>
    <form method="post" action="login">
        Username: <input type="text" name="username"><br><br>
        Password: <input type="password" name="password"><br><br>
        <input type="submit" value="Login">
    </form>
    <% if ("true".equals(request.getParameter("error"))) { %>
        <p style="color:red;">Invalid username or password.</p>
    <% } %>
</body>
</html>

<!DOCTYPE html>
<html>
<head>
    <title>Index</title>
</head>
<body>
    <h2>Welcome to the Home Page</h2>
    <a href="login.jsp">Login</a>
</body>
</html>

<!DOCTYPE html>
<html>
<head>
    <title>Secret Settings</title>
</head>
<body>
    <h1>Secret settings</h1>
    <a href="logout">Logout</a>
</body>
</html>