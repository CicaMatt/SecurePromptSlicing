import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    private static final String CORRECT_USERNAME = "admin";
    private static final String CORRECT_PASSWORD = "password123";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (CORRECT_USERNAME.equals(username) && CORRECT_PASSWORD.equals(password)) {
            request.getSession().setAttribute("username", username);
            response.sendRedirect("secret");
        } else {
            response.sendRedirect("login?error=true");
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        if (request.getParameter("error") != null) {
            request.setAttribute("errorMessage", "Invalid credentials!");
        }
        request.getRequestDispatcher("/WEB-INF/login.jsp").forward(request, response);
    }
}

@WebServlet("/secret")
public class SecretServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        if (request.getSession().getAttribute("username") == null) {
            response.sendRedirect("login");
        } else {
            request.getRequestDispatcher("/WEB-INF/secret.jsp").forward(request, response);
        }
    }
}

// login.jsp
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head><title>Login</title></head>
<body>
<form method="post" action="login">
    <label>Username:</label><br>
    <input type="text" name="username"><br>
    <label>Password:</label><br>
    <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
<% if (request.getAttribute("errorMessage") != null) { %>
<p style="color: red;"><%= request.getAttribute("errorMessage") %></p>
<% } %>
<a href="secret">Go to Secret Page</a>
</body>
</html>

// secret.jsp
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head><title>Secret Settings</title></head>
<body>
<h1>Secret settings</h1>
<a href="login">Back to Login</a>
</body>
</html>