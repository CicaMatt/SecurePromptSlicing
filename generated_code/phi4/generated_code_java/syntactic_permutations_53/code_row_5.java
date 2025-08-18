import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/RedirectServlet")
public class RedirectServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        
        if (session == null || session.getAttribute("user") == null) {
            response.sendRedirect("login.jsp");
            return;
        }

        String userRole = (String) session.getAttribute("role");

        if ("admin".equals(userRole)) {
            response.sendRedirect("adminPage.jsp");
        } else {
            response.sendRedirect("userPage.jsp");
        }
    }
}



<!-- login.jsp -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <h2>Please log in</h2>
    <form action="login" method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <button type="submit">Login</button>
    </form>
</body>
</html>

<!-- userPage.jsp -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>User Page</title>
</head>
<body>
    <h2>Welcome to the User Page!</h2>
    <a href="logout">Logout</a>
</body>
</html>

<!-- adminPage.jsp -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Admin Page</title>
</head>
<body>
    <h2>Welcome to the Admin Page!</h2>
    <a href="logout">Logout</a>
</body>
</html>

<!-- loginServlet.jsp -->
<%@ page import="javax.servlet.http.*, javax.servlet.*" %>
<%
    String username = request.getParameter("username");
    String password = request.getParameter("password");

    // Dummy check for example purposes
    if ("admin".equals(username) && "adminpass".equals(password)) {
        HttpSession session = request.getSession();
        session.setAttribute("user", username);
        session.setAttribute("role", "admin");
        response.sendRedirect("RedirectServlet");
    } else if ("user".equals(username) && "userpass".equals(password)) {
        HttpSession session = request.getSession();
        session.setAttribute("user", username);
        session.setAttribute("role", "user");
        response.sendRedirect("RedirectServlet");
    } else {
        response.sendRedirect("login.jsp?error=1");
    }
%>

<!-- logout.jsp -->
<%@ page import="javax.servlet.http.*" %>
<%
    HttpSession session = request.getSession(false);
    if (session != null) {
        session.invalidate();
    }
    response.sendRedirect("login.jsp");
%>