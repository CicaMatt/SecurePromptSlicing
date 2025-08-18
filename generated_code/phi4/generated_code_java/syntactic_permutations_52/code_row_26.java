import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
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

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.getRequestDispatcher("/WEB-INF/views/login.jsp").forward(request, response);
    }
}

@WebServlet("/")
public class IndexServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.getRequestDispatcher("/WEB-INF/views/index.jsp").forward(request, response);
    }
}

@WebServlet("/secret")
public class SecretServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);

        if (session != null && "admin".equals(session.getAttribute("username"))) {
            request.getRequestDispatcher("/WEB-INF/views/secret.jsp").forward(request, response);
        } else {
            response.sendRedirect("login");
        }
    }
}



<!-- WEB-INF/views/login.jsp -->
<!DOCTYPE html>
<html>
<head>
    <title>Login</title>
</head>
<body>
    <form action="login" method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <button type="submit">Login</button>
    </form>
    <% if (request.getParameter("error") != null) { %>
        <p>Invalid username or password.</p>
    <% } %>
</body>
</html>



<!-- WEB-INF/views/index.jsp -->
<!DOCTYPE html>
<html>
<head>
    <title>Index</title>
</head>
<body>
    <h1>Welcome to the Index Page</h1>
    <a href="login">Login</a>
</body>
</html>



<!-- WEB-INF/views/secret.jsp -->
<!DOCTYPE html>
<html>
<head>
    <title>Secret Settings</title>
</head>
<body>
    <h1>Secret settings</h1>
</body>
</html>


Make sure to configure your web application with the appropriate `web.xml` or use annotations as shown, and deploy it on a servlet container like Tomcat.