import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

@WebServlet("/Register")
public class RegisterServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = hashPassword(request.getParameter("password"));

        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/yourDatabase", 
                "root", 
                "yourPassword")) {

            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, username);
                statement.setString(2, password);
                statement.executeUpdate();
            }
        } catch (Exception e) {
            throw new ServletException("Database error", e);
        }

        response.sendRedirect("registrationSuccess.html");
    }

    private String hashPassword(String password) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hashedBytes = md.digest(password.getBytes());
        StringBuilder sb = new StringBuilder();
        for (byte b : hashedBytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.sendRedirect("register.html");
    }
}


**Note:** Make sure to replace `yourDatabase`, `root`, and `yourPassword` with your actual database name, username, and password. Also, ensure you have a table named `users` in your database with at least two columns: `username` (VARCHAR) and `password` (VARCHAR).

Additionally, create the following HTML files:

**register.html**

<!DOCTYPE html>
<html>
<head>
    <title>Register</title>
</head>
<body>
    <form action="Register" method="post">
        <label for="username">Username:</label><br>
        <input type="text" id="username" name="username"><br>
        <label for="password">Password:</label><br>
        <input type="password" id="password" name="password"><br><br>
        <input type="submit" value="Register">
    </form>
</body>
</html>


**registrationSuccess.html**

<!DOCTYPE html>
<html>
<head>
    <title>Registration Success</title>
</head>
<body>
    <h1>Registration Successful!</h1>
    <p>You can now <a href="register.html">register another user</a>.</p>
</body>
</html>


**Dependencies:**
- Ensure you have a MySQL server running and accessible.
- Include the MySQL Connector/J library in your project's classpath. You can download it from [MySQL Connector/J](https://dev.mysql.com/downloads/connector/j/).
- Configure your servlet container (e.g., Apache Tomcat) to deploy this web application.