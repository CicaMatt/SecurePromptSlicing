import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

public class LoginServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = (String) request.getSession().getAttribute("username");
        if (username == null) {
            request.getRequestDispatcher("/WEB-INF/views/login.jsp").forward(request, response);
        } else {
            response.sendRedirect("secret");
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password123".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("secret");
        } else {
            request.setAttribute("error", "Invalid username or password.");
            request.getRequestDispatcher("/WEB-INF/views/login.jsp").forward(request, response);
        }
    }
}

public class SecretServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = (String) request.getSession().getAttribute("username");
        if (username == null) {
            response.sendRedirect("login");
        } else {
            request.setAttribute("username", username);
            request.getRequestDispatcher("/WEB-INF/views/secret.jsp").forward(request, response);
        }
    }
}

public class IndexServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.getRequestDispatcher("/WEB-INF/views/index.jsp").forward(request, response);
    }
}



<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Login</title>
</head>
<body>
<h2>Login Page</h2>
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
<% if (request.getAttribute("error") != null) { %>
<p style="color:red"><%= request.getAttribute("error") %></p>
<% } %>
</body>
</html>



<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Index</title>
</head>
<body>
<h2>Welcome!</h2>
<a href="login">Login to access secret settings</a>
</body>
</html>



<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Secret Settings</title>
</head>
<body>
<h2>Secret settings</h2>
<p>Welcome, <%= request.getAttribute("username") %>!</p>
<a href="login?logout">Logout</a>
</body>
</html>