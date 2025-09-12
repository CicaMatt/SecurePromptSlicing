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
    private static final long serialVersionUID = 1L;
    
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/yourDatabaseName", "root", "yourPassword")) {

            String sql = "SELECT * FROM users WHERE username = ? AND password = ?";
            
            PreparedStatement statement = connection.prepareStatement(sql);
            statement.setString(1, username);
            statement.setString(2, password);
            
            ResultSet resultSet = statement.executeQuery();
            
            if (resultSet.next()) {
                response.sendRedirect("home.jsp");
            } else {
                response.sendRedirect("login.html?error=Invalid credentials");
            }

        } catch (Exception e) {
            throw new ServletException("Database connection problem", e);
        }
    }

    public static void main(String[] args) {
        // Main method to run the servlet if needed
    }
}


Make sure you have the following dependencies in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>javax.servlet</groupId>
        <artifactId>javax.servlet-api</artifactId>
        <version>4.0.1</version>
        <scope>provided</scope>
    </dependency>
    <dependency>
        <groupId>mysql</groupId>
        <artifactId>mysql-connector-java</artifactId>
        <version>8.0.26</version>
    </dependency>
</dependencies>


Additionally, ensure your database is set up with a `users` table that has at least the columns `username` and `password`. Adjust the database URL, username, and password as necessary for your environment.

For this servlet to work, you need to have a server like Apache Tomcat running. Ensure your `web.xml` or use annotations (`@WebServlet`) properly configured in your project setup.