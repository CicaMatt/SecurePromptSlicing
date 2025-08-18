import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (isValidUser(username, password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            response.sendRedirect("home.jsp"); // Assuming there is a home.jsp page
        } else {
            response.sendRedirect("login.html");
        }
    }

    private boolean isValidUser(String username, String password) {
        // This should be replaced with actual user validation logic, e.g., database check.
        return "admin".equals(username) && "password123".equals(password);
    }
}

// HTML login page (login.html)
/*
<!DOCTYPE html>
<html>
<head>
    <title>Login</title>
</head>
<body>
    <form action="login" method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>
*/

// JSP home page (home.jsp)
/*
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Home</title>
</head>
<body>
    <h1>Welcome, <%= request.getSession().getAttribute("user") %>!</h1>
    <a href="logout">Logout</a>
</body>
</html>
*/

// JSP logout page (logout.jsp)
/*
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%
    HttpSession session = request.getSession(false);
    if (session != null) {
        session.invalidate();
    }
%>
<!DOCTYPE html>
<html>
<head>
    <title>Logout</title>
</head>
<body>
    <h1>You have been logged out.</h1>
    <a href="login.html">Login Again</a>
</body>
</html>
*/