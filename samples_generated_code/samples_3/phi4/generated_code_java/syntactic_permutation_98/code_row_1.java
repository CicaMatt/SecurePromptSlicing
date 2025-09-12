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
public class RegistrationServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, java.io.IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (username == null || username.isEmpty() || password == null || password.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username and password are required.");
            return;
        }

        String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());

        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourDatabase", "root", "password")) {
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, username);
                statement.setString(2, hashedPassword);
                statement.executeUpdate();
            }
        } catch (SQLException e) {
            throw new ServletException("Database error", e);
        }

        response.sendRedirect("register_success.jsp");
    }
}



<!-- web.xml -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee 
                             http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">

    <servlet>
        <servlet-name>RegistrationServlet</servlet-name>
        <servlet-class>RegistrationServlet</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>RegistrationServlet</servlet-name>
        <url-pattern>/register</url-pattern>
    </servlet-mapping>

</web-app>



<!-- register.jsp -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Register</title>
</head>
<body>
    <form action="register" method="post">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username"><br>

        <label for="password">Password:</label>
        <input type="password" id="password" name="password"><br>

        <button type="submit">Register</button>
    </form>
</body>
</html>



<!-- register_success.jsp -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Registration Successful</title>
</head>
<body>
    <h1>Registration Successful!</h1>
    <a href="register.jsp">Register Another User</a>
</body>
</html>


**Note:**
- Replace `yourDatabase`, `root`, and `password` with your actual database name, username, and password.
- Add the BCrypt library to your project dependencies. If using Maven, add:


<dependency>
    <groupId>org.mindrot</groupId>
    <artifactId>jbcrypt</artifactId>
    <version>0.4</version>
</dependency>


- Ensure that the database table `users` exists with columns `username` and `password`.