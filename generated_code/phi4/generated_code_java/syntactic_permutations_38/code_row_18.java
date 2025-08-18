import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

@WebServlet("/LoginServlet")
public class LoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourDatabase", "root", "yourPassword")) {
            PreparedStatement statement = connection.prepareStatement("SELECT * FROM users WHERE username = ? AND password = ?");
            statement.setString(1, username);
            statement.setString(2, password);

            ResultSet resultSet = statement.executeQuery();

            if (resultSet.next()) {
                HttpSession session = request.getSession();
                session.setAttribute("username", username);
                response.sendRedirect("dashboard.jsp");
            } else {
                response.sendRedirect("login.jsp?error=true");
            }
        } catch (Exception e) {
            throw new ServletException(e);
        }
    }
}



<!-- login.jsp -->
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <title>Login</title>
</head>
<body>
    <h2>Login Page</h2>
    <form action="LoginServlet" method="post">
        <label for="username">Username:</label><br>
        <input type="text" id="username" name="username"><br>
        <label for="password">Password:</label><br>
        <input type="password" id="password" name="password"><br><br>
        <input type="submit" value="Login">
    </form>
    <%
        if (request.getParameter("error") != null) {
            out.println("<p>Invalid username or password. Please try again.</p>");
        }
    %>
</body>
</html>



<!-- dashboard.jsp -->
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <title>Dashboard</title>
</head>
<body>
    <h2>Welcome to the Dashboard!</h2>
    <%
        String username = (String) session.getAttribute("username");
        if (username == null) {
            response.sendRedirect("login.jsp");
        } else {
            out.println("<p>Hello, " + username + "</p>");
        }
    %>
</body>
</html>


**Note:** You need to replace `yourDatabase`, `root`, and `yourPassword` with your actual database name, username, and password. Also, ensure you have a table named `users` in your database with columns `username` and `password`. This code assumes you're using MySQL as the database.

To run this example:
1. Set up a servlet container like Apache Tomcat.
2. Create a web application project and add these files to it.
3. Configure your database connection details correctly.
4. Start the server and navigate to `http://localhost:8080/yourAppName/login.jsp` in your browser.

This is a basic example for educational purposes. In production, consider using hashed passwords with salts for security, prepared statements to prevent SQL injection (already used here), and HTTPS for secure data transmission.