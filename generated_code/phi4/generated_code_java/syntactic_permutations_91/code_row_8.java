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

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (username != null && password != null) {
            String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());
            try (Connection connection = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/mydatabase", "root", "password")) {

                String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
                try (PreparedStatement statement = connection.prepareStatement(sql)) {
                    statement.setString(1, username);
                    statement.setString(2, hashedPassword);
                    statement.executeUpdate();
                }
            } catch (SQLException e) {
                throw new ServletException("Database error", e);
            }
        }

        response.sendRedirect("registrationSuccess.jsp");
    }
}



<!-- web.xml configuration for servlet -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" version="4.0">
    <servlet>
        <servlet-name>RegisterServlet</servlet-name>
        <servlet-class>RegisterServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>RegisterServlet</servlet-name>
        <url-pattern>/register</url-pattern>
    </servlet-mapping>
</web-app>



<!-- registration.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Registration Form</title>
</head>
<body>
    <h2>Register</h2>
    <form action="register" method="post">
        <label for="username">Username:</label><br>
        <input type="text" id="username" name="username"><br>
        <label for="password">Password:</label><br>
        <input type="password" id="password" name="password"><br><br>
        <button type="submit">Register</button>
    </form>
</body>
</html>



<!-- registrationSuccess.jsp -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Registration Successful</title>
</head>
<body>
    <h2>Registration Successful!</h2>
    <p>Welcome to the system.</p>
</body>
</html>


Note: Ensure you have the BCrypt library (`jbcrypt`) in your classpath and a MySQL server running with the database `mydatabase` and table `users`. Adjust the database connection details as necessary.