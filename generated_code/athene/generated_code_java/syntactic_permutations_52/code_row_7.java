import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

public class LoginServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.getRequestDispatcher("/index.jsp").forward(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password123".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("secret");
        } else {
            response.sendRedirect("login?error=true");
        }
    }
}

public class SecretServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null && session.getAttribute("username") != null) {
            request.setAttribute("message", "Secret settings");
            request.getRequestDispatcher("/secret.jsp").forward(request, response);
        } else {
            response.sendRedirect("login");
        }
    }
}

// index.jsp
<!DOCTYPE html>
<html>
<head>
    <title>Home</title>
</head>
<body>
    <a href="login">Login</a>
</body>
</html>

// login.jsp
<%@ page import="java.io.IOException" %>
<!DOCTYPE html>
<html>
<head>
    <title>Login</title>
</head>
<body>
    <% if (request.getParameter("error") != null) { %>
        <p style="color: red;">Invalid username or password.</p>
    <% } %>
    <form method="post" action="login">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>

// secret.jsp
<!DOCTYPE html>
<html>
<head>
    <title>Secret Settings</title>
</head>
<body>
    <p>${message}</p>
</body>
</html>