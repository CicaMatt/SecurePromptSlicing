import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class LoginServlet extends HttpServlet {
    private static final String JDBC_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "youruser";
    private static final String PASS = "yourpassword";

    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        boolean isValidUser = validate(username, password);

        if (isValidUser) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            response.sendRedirect("home.jsp");
        } else {
            response.sendRedirect("login.html");
        }
    }

    private boolean validate(String username, String password) {
        try (Connection connection = DriverManager.getConnection(JDBC_URL, USER, PASS)) {
            String sql = "SELECT * FROM users WHERE name=? AND password=?";
            try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                preparedStatement.setString(1, username);
                preparedStatement.setString(2, password);

                ResultSet resultSet = preparedStatement.executeQuery();
                return resultSet.next();
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            throw new ServletException(e);
        }
    }
}



<!-- login.html -->
<!DOCTYPE html>
<html>
<head>
    <title>Login</title>
</head>
<body>
    <h2>Login Form</h2>
    <form action="LoginServlet" method="post">
        Username: <input type="text" name="username"><br><br>
        Password: <input type="password" name="password"><br><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>



<!-- home.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Home Page</title>
</head>
<body>
    <h2>Welcome, <%= session.getAttribute("user") %>!</h2>
    <a href="login.html">Logout</a>
</body>
</html>