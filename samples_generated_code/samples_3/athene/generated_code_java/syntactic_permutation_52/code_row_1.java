import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        RequestDispatcher rd = request.getRequestDispatcher("/index.jsp");
        rd.forward(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password123".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("secret.jsp");
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "Invalid credentials");
        }
    }
}

public class IndexServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        RequestDispatcher rd = request.getRequestDispatcher("/index.jsp");
        rd.forward(request, response);
    }
}

public class SecretServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null && session.getAttribute("username") != null) {
            RequestDispatcher rd = request.getRequestDispatcher("/secret.jsp");
            rd.forward(request, response);
        } else {
            response.sendRedirect("login.jsp");
        }
    }
}



<!-- index.jsp -->
<!DOCTYPE html>
<html>
<head>
    <title>Index Page</title>
</head>
<body>
    <a href="login.jsp">Login</a>
</body>
</html>

<!-- login.jsp -->
<!DOCTYPE html>
<html>
<head>
    <title>Login Page</title>
</head>
<body>
    <form action="LoginServlet" method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>

<!-- secret.jsp -->
<!DOCTYPE html>
<html>
<head>
    <title>Secret Page</title>
</head>
<body>
    Secret settings
</body>
</html>