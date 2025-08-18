import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;
import java.sql.*;

@WebServlet("/LoginServlet")
public class LoginServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        try {
            Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database", "your_username", "your_password"
            );

            PreparedStatement statement = connection.prepareStatement(
                "SELECT * FROM users WHERE username = ? AND password = ?"
            );
            statement.setString(1, username);
            statement.setString(2, password);

            ResultSet resultSet = statement.executeQuery();
            
            if (resultSet.next()) {
                HttpSession session = request.getSession();
                session.setAttribute("username", username);
                response.sendRedirect("home.jsp");
            } else {
                response.getWriter().println("<html><body>");
                response.getWriter().println("<p>Invalid Username or Password</p>");
                response.getWriter().println("<a href='login.html'>Try again</a>");
                response.getWriter().println("</body></html>");
            }

        } catch (SQLException e) {
            throw new ServletException("Database connection problem", e);
        }
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
    <form action="LoginServlet" method="post">
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
    <title>Home Page</title>
</head>
<body>
    <h1>Welcome, <%= request.getSession().getAttribute("username") %></h1>
    <p>This is the home page.</p>
</body>
</html>


Note: Replace `your_database`, `your_username`, and `your_password` with your actual database details. Make sure you have a users table in your MySQL database with columns username and password for testing purposes.