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

        if (username != null && !username.isEmpty() && password != null && !password.isEmpty()) {
            String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());

            try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database", "root", "password")) {
                String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
                
                try (PreparedStatement statement = connection.prepareStatement(sql)) {
                    statement.setString(1, username);
                    statement.setString(2, hashedPassword);
                    
                    int rowsInserted = statement.executeUpdate();
                    if (rowsInserted > 0) {
                        response.getWriter().write("User registered successfully!");
                    }
                }
            } catch (SQLException e) {
                throw new ServletException(e);
            }
        } else {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Invalid input");
        }
    }

    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            throw new ServletException("MySQL JDBC Driver not found", e);
        }
    }
}


To run this code, you'll need:
- A servlet container like Apache Tomcat.
- A MySQL database with a table `users` having columns `username` and `password`.
- The BCrypt library for password hashing. Add the BCrypt dependency to your project.

For Maven projects, include in your `pom.xml`:


<dependency>
    <groupId>org.mindrot</groupId>
    <artifactId>jbcrypt</artifactId>
    <version>0.4</version>
</dependency>


Ensure MySQL JDBC driver is available on the classpath.