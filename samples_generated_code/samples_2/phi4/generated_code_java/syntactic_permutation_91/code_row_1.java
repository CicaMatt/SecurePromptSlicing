import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

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

        if (username == null || password == null) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username and password are required.");
            return;
        }

        try (Connection connection = getConnection()) {
            String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());
            PreparedStatement statement = connection.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)");
            statement.setString(1, username);
            statement.setString(2, hashedPassword);
            int result = statement.executeUpdate();

            if (result > 0) {
                response.getWriter().write("User registered successfully.");
            } else {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Registration failed.");
            }
        } catch (Exception e) {
            throw new ServletException(e);
        }
    }

    private Connection getConnection() throws Exception {
        String url = "jdbc:mysql://localhost:3306/yourdatabase";
        String user = "root";
        String password = "yourpassword";

        Class.forName("com.mysql.cj.jdbc.Driver");
        return DriverManager.getConnection(url, user, password);
    }
}



<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Register</title>
</head>
<body>
    <h2>User Registration</h2>
    <form action="register" method="post">
        <label for="username">Username:</label><br>
        <input type="text" id="username" name="username"><br><br>
        <label for="password">Password:</label><br>
        <input type="password" id="password" name="password"><br><br>
        <button type="submit">Register</button>
    </form>
</body>
</html>


**Note:** Replace `yourdatabase`, `root`, and `yourpassword` with your actual database name, username, and password. You also need to have a MySQL server running and the `users` table created in your database:


CREATE TABLE users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(255) NOT NULL UNIQUE,
    password VARCHAR(255) NOT NULL
);


**Dependencies:**
- Add the following dependencies to your `pom.xml` if you are using Maven:
  
  <dependency>
      <groupId>org.mindrot</groupId>
      <artifactId>jbcrypt</artifactId>
      <version>0.4</version>
  </dependency>
  <dependency>
      <groupId>mysql</groupId>
      <artifactId>mysql-connector-java</artifactId>
      <version>8.0.26</version>
  </dependency>
  
- Ensure you have a servlet container like Apache Tomcat to deploy the web application.