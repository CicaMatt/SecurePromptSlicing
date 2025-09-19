import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet("/login")
@MultipartConfig
public class LoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        boolean isValidUser = checkCredentials(username, password);

        if (isValidUser) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            response.sendRedirect("home.jsp");
        } else {
            response.sendRedirect("login.html");
        }
    }

    private boolean checkCredentials(String username, String password) {
        // Dummy validation logic for demonstration purposes
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
        <label for="username">Username:</label><br>
        <input type="text" id="username" name="username"><br>
        <label for="password">Password:</label><br>
        <input type="password" id="password" name="password"><br><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>



<!-- home.jsp -->
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Home</title>
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
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null) {
            session.invalidate();
        }
        response.sendRedirect("login.html");
    }
}


This code includes a simple servlet `LoginServlet` to handle login requests, a static HTML file `login.html` for the login form, and a JSP file `home.jsp` as the landing page after successful authentication. A `LogoutServlet` is also provided to handle session invalidation on logout. This example uses hard-coded credentials for simplicity; in a real application, you would replace this with database validation logic.

To run this code, it must be deployed in a Java servlet container such as Apache Tomcat. You will need to configure the web.xml file or use annotations (as shown) to map servlets to URLs. Additionally, ensure that your web application has the necessary permissions and configurations set up to access a database if you plan to implement real authentication logic.