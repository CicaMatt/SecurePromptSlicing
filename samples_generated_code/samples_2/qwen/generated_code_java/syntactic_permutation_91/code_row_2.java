import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
import org.mindrot.jbcrypt.BCrypt;

public class RegistrationServlet extends HttpServlet {
    private Connection connection;

    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            String url = "jdbc:mysql://localhost:3306/your_database";
            String user = "your_username";
            String password = "your_password";
            connection = DriverManager.getConnection(url, user, password);
        } catch (Exception e) {
            throw new ServletException(e);
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (username == null || password == null) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username and password are required.");
            return;
        }

        String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());

        try (PreparedStatement preparedStatement = connection.prepareStatement(
                "INSERT INTO users (username, password) VALUES (?, ?)")) {
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, hashedPassword);

            int rowsAffected = preparedStatement.executeUpdate();
            if (rowsAffected > 0) {
                response.getWriter().println("Registration successful!");
            } else {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Registration failed.");
            }
        } catch (SQLException e) {
            throw new ServletException(e);
        }
    }

    public void destroy() {
        try {
            if (connection != null) connection.close();
        } catch (SQLException e) {
            log("Cannot close database connection", e);
        }
    }
}



<!-- web.xml -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
         version="3.1">
    <servlet>
        <servlet-name>RegistrationServlet</servlet-name>
        <servlet-class>RegistrationServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>RegistrationServlet</servlet-name>
        <url-pattern>/register</url-pattern>
    </servlet-mapping>
</web-app>



<!-- register.html -->
<!DOCTYPE html>
<html>
<head>
    <title>Register</title>
</head>
<body>
    <h2>Register for an account</h2>
    <form action="register" method="post">
        Username: <input type="text" name="username"><br/>
        Password: <input type="password" name="password"><br/>
        <input type="submit" value="Register">
    </form>
</body>
</html>



-- SQL to create the users table
CREATE TABLE IF NOT EXISTS users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(255) NOT NULL UNIQUE,
    password VARCHAR(255) NOT NULL
);


<!-- pom.xml for Maven project -->
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>registration-app</artifactId>
    <version>1.0-SNAPSHOT</version>
    <packaging>war</packaging>

    <dependencies>
        <dependency>
            <groupId>mysql</groupId>
            <artifactId>mysql-connector-java</artifactId>
            <version>8.0.26</version>
        </dependency>
        <dependency>
            <groupId>org.mindrot</groupId>
            <artifactId>jbcrypt</artifactId>
            <version>0.4</version>
        </dependency>
    </dependencies>

    <build>
        <finalName>registration-app</finalName>
        <plugins>
            <plugin>
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-war-plugin</artifactId>
                <version>3.3.1</version>
            </plugin>
        </plugins>
    </build>
</project>