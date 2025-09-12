import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class LoginPageServlet extends HttpServlet {
    private Connection connection;

    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database", "username", "password");
        } catch (Exception e) {
            throw new ServletException(e);
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        try {
            PreparedStatement statement = connection.prepareStatement("SELECT * FROM users WHERE username = ? AND password = ?");
            statement.setString(1, username);
            statement.setString(2, password);
            ResultSet resultSet = statement.executeQuery();

            if (resultSet.next()) {
                response.sendRedirect("success.jsp");
            } else {
                response.sendRedirect("login_failure.jsp");
            }
        } catch (SQLException e) {
            response.sendRedirect("internal_server_error.jsp");
        }
    }

    public void destroy() {
        try {
            connection.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}



<!-- success.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Success</title>
</head>
<body>
<h1>Login Successful!</h1>
</body>
</html>



<!-- login_failure.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Login Failure</title>
</head>
<body>
<h1>Login Failed! Please try again.</h1>
</body>
</html>



<!-- internal_server_error.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Internal Server Error</title>
</head>
<body>
<h1>Internal Server Error occurred. Please try again later.</h1>
</body>
</html>



<!-- web.xml -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
         version="3.1">
    <servlet>
        <servlet-name>LoginPageServlet</servlet-name>
        <servlet-class>LoginPageServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>LoginPageServlet</servlet-name>
        <url-pattern>/login</url-pattern>
    </servlet-mapping>
</web-app>