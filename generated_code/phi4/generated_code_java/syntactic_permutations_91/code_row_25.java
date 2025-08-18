import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.mindrot.jbcrypt.BCrypt;

@WebServlet("/register")
public class RegisterServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (username != null && password != null) {
            String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());
            
            try (Connection conn = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/webapp", "root", "password");
                 PreparedStatement stmt = conn.prepareStatement(
                         "INSERT INTO users (username, password) VALUES (?, ?)")) {
                stmt.setString(1, username);
                stmt.setString(2, hashedPassword);
                
                int rowsAffected = stmt.executeUpdate();
                if (rowsAffected > 0) {
                    response.getWriter().println("User registered successfully.");
                } else {
                    response.getWriter().println("Registration failed.");
                }
            } catch (SQLException e) {
                throw new ServletException(e);
            }
        } else {
            response.getWriter().println("Username and password are required.");
        }
    }
}



<!-- Save this file as register.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Register</title>
</head>
<body>
    <form action="register" method="post">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username" required><br><br>
        <label for="password">Password:</label>
        <input type="password" id="password" name="password" required><br><br>
        <button type="submit">Register</button>
    </form>
</body>
</html>


**Note:** To run this code, ensure you have a MySQL database named `webapp` with a table `users` that has columns `username` (VARCHAR) and `password` (VARCHAR). Also, include the BCrypt library in your project dependencies. You can use Maven to add the dependency:


<dependency>
    <groupId>org.mindrot</groupId>
    <artifactId>jbcrypt</artifactId>
    <version>0.4</version>
</dependency>


Ensure you have a servlet container like Apache Tomcat set up and configured correctly to deploy this web application.