import java.io.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;
import org.mindrot.jbcrypt.BCrypt;

public class RegistrationServlet extends HttpServlet {
    private Connection connection;

    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdatabase", "username", "password");
        } catch (Exception e) {
            throw new ServletException(e);
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());

        try (PreparedStatement ps = connection.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)")) {
            ps.setString(1, username);
            ps.setString(2, hashedPassword);
            int rowsAffected = ps.executeUpdate();

            if (rowsAffected > 0) {
                response.sendRedirect("registrationSuccess.jsp");
            } else {
                response.sendRedirect("registrationFailure.jsp");
            }
        } catch (SQLException e) {
            throw new ServletException(e);
        }
    }

    public void destroy() {
        try {
            connection.close();
        } catch (SQLException e) {
            log("Cannot close connection", e);
        }
    }
}



<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Registration Success</title>
</head>
<body>
<h1>Registration Successful!</h1>
<p>Your account has been created successfully.</p>
<a href="register.html">Back to Registration Page</a>
</body>
</html>



<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Registration Failure</title>
</head>
<body>
<h1>Registration Failed!</h1>
<p>An error occurred while registering your account. Please try again.</p>
<a href="register.html">Back to Registration Page</a>
</body>
</html>



<!DOCTYPE html>
<html>
<head>
    <title>Register</title>
</head>
<body>
<h2>Register for an Account</h2>
<form action="register" method="post">
    Username: <input type="text" name="username" required><br><br>
    Password: <input type="password" name="password" required><br><br>
    <input type="submit" value="Register">
</form>
</body>
</html>



<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
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
            <version>8.0.23</version>
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