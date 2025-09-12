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
import javax.servlet.http.HttpSession;

@WebServlet("/LoginServlet")
public class LoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (authenticateUser(username, password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            response.sendRedirect("home.jsp"); // Redirect to home page after successful login
        } else {
            response.sendRedirect("login.jsp?error=Invalid Username or Password"); // Redirect back to the login page with an error message
        }
    }

    private boolean authenticateUser(String username, String password) {
        Connection connection = null;
        PreparedStatement statement = null;
        ResultSet resultSet = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/your_database", "db_user", "db_password");

            String sql = "SELECT * FROM users WHERE username = ? AND password = ?";
            statement = connection.prepareStatement(sql);
            statement.setString(1, username);
            statement.setString(2, password);

            resultSet = statement.executeQuery();
            return resultSet.next(); // Return true if user exists

        } catch (Exception e) {
            e.printStackTrace();
            return false;
        } finally {
            try { if (resultSet != null) resultSet.close(); } catch (Exception e) {}
            try { if (statement != null) statement.close(); } catch (Exception e) {}
            try { if (connection != null) connection.close(); } catch (Exception e) {}
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request, response);
    }
}



<!-- login.jsp -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <h2>Login Page</h2>
    <form action="LoginServlet" method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br><br>
        <button type="submit">Login</button>
    </form>
    <% if (request.getParameter("error") != null) { %>
        <p style="color:red;"><%= request.getParameter("error") %></p>
    <% } %>
</body>
</html>



<!-- home.jsp -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Home Page</title>
</head>
<body>
    <h2>Welcome, <%= request.getSession().getAttribute("user") %>!</h2>
    <a href="logout">Logout</a>
</body>
</html>



import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/logout")
public class LogoutServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null) {
            session.invalidate();
        }
        response.sendRedirect("login.jsp"); // Redirect to login page after logout
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}


Note: Replace `"jdbc:mysql://localhost:3306/your_database"`, `"db_user"`, and `"db_password"` with your actual database URL, username, and password. Also, ensure you have the MySQL JDBC driver in your classpath.