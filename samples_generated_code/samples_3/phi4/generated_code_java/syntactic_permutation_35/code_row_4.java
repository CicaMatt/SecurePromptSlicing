import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (isValidUser(username, password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            response.sendRedirect("home.jsp");
        } else {
            response.sendRedirect("login.html?error=true");
        }
    }

    private boolean isValidUser(String username, String password) {
        // Simulate a user validation (in real applications, use database or other secure methods)
        return "admin".equals(username) && "password123".equals(password);
    }
}



<!-- login.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
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



<!-- home.jsp -->
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Home Page</title>
</head>
<body>
    <h1>Welcome, <%= request.getSession().getAttribute("user") %></h1>
    <a href="logout">Logout</a>
</body>
</html>



import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

@WebServlet("/logout")
public class LogoutServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        HttpSession session = request.getSession(false);
        if (session != null) {
            session.invalidate();
        }
        response.sendRedirect("login.html");
    }
}


**Note**: Ensure you have a servlet container like Apache Tomcat set up to run this code. Additionally, ensure `web.xml` is configured or use the `@WebServlet` annotation as shown.