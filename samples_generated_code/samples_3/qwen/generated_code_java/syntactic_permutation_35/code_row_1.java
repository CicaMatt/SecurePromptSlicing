import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class LoginServlet extends HttpServlet {
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

        boolean isValidUser = false;
        try (PreparedStatement statement = connection.prepareStatement("SELECT * FROM users WHERE username=? AND password=?")) {
            statement.setString(1, username);
            statement.setString(2, password);
            ResultSet resultSet = statement.executeQuery();
            isValidUser = resultSet.next();
        } catch (SQLException e) {
            throw new ServletException(e);
        }

        if (isValidUser) {
            response.sendRedirect("home.html");
        } else {
            response.sendRedirect("login.html");
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



<!DOCTYPE html>
<html>
<head>
    <title>Login</title>
</head>
<body>
    <form action="LoginServlet" method="post">
        Username: <input type="text" name="username"><br/>
        Password: <input type="password" name="password"><br/>
        <input type="submit" value="Login">
    </form>
</body>
</html>



<!DOCTYPE html>
<html>
<head>
    <title>Home</title>
</head>
<body>
    <h1>Welcome to the Home Page!</h1>
</body>
</html>