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

        if (username != null && password != null && !username.isEmpty() && !password.isEmpty()) {
            try {
                String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());

                Connection conn = DriverManager.getConnection(
                        "jdbc:mysql://localhost:3306/webapp", "root", "password");

                String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
                PreparedStatement statement = conn.prepareStatement(sql);
                statement.setString(1, username);
                statement.setString(2, hashedPassword);

                int result = statement.executeUpdate();
                if (result > 0) {
                    response.getWriter().println("User registered successfully.");
                } else {
                    response.getWriter().println("Registration failed.");
                }

                statement.close();
                conn.close();
            } catch (SQLException e) {
                throw new ServletException("Database error", e);
            }
        } else {
            response.getWriter().println("Username and password cannot be empty.");
        }
    }
}


Additionally, ensure your web application is configured to use a servlet container like Apache Tomcat. You also need to set up the database schema as follows:


CREATE DATABASE IF NOT EXISTS webapp;

USE webapp;

CREATE TABLE IF NOT EXISTS users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(255) UNIQUE NOT NULL,
    password VARCHAR(255) NOT NULL
);


Make sure you have `bcrypt` library in your project's dependencies. You can add it using Maven by including:


<dependency>
    <groupId>org.mindrot</groupId>
    <artifactId>jbcrypt</artifactId>
    <version>0.4</version>
</dependency>


Ensure that the database URL, username, and password are configured correctly as per your setup in `DriverManager.getConnection`.