import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            PreparedStatement ps = connection.prepareStatement("SELECT * FROM users WHERE username=? AND password=?");
            ps.setString(1, username);
            ps.setString(2, password);

            ResultSet rs = ps.executeQuery();

            if (rs.next()) {
                response.sendRedirect("home.jsp"); // Redirect to home page
            } else {
                response.sendRedirect("login.html"); // Redirect back to login page
            }
        } catch (Exception e) {
            throw new ServletException(e);
        }
    }

    public static void main(String[] args) throws Exception {
        // Ensure the MySQL JDBC driver is loaded
        Class.forName("com.mysql.cj.jdbc.Driver");
        
        // Start a simple HTTP server to test locally, replace with proper deployment in production
        org.eclipse.jetty.server.Server server = new org.eclipse.jetty.server.Server(8080);
        server.setHandler(new org.eclipse.jetty.servlet.ServletContextHandler());
        ((org.eclipse.jetty.servlet.ServletContextHandler)server.getHandler()).addServlet(
            org.eclipse.jetty.servlet.ServletHolder.newInstance(LoginServlet.class),
            "/login"
        );
        
        server.start();
        server.join();
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
        <label for="username">Username:</label>
        <input type="text" id="username" name="username"><br><br>
        
        <label for="password">Password:</label>
        <input type="password" id="password" name="password"><br><br>

        <button type="submit">Login</button>
    </form>
</body>
</html>



<!-- home.jsp -->
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Home Page</title>
</head>
<body>
    <h1>Welcome to the Home Page!</h1>
</body>
</html>


Note: Ensure you have a MySQL database set up with a table named `users` containing columns for `username` and `password`. Adjust the database connection details (`DB_URL`, `USER`, and `PASS`) as necessary. Also, ensure that Jetty is added to your project's dependencies if using it locally, or configure this servlet within your preferred Java web server environment for production use.