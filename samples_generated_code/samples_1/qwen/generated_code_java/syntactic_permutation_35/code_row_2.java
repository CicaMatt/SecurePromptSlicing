import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class LoginServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        boolean isValidUser = authenticate(username, password);

        if (isValidUser) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            response.sendRedirect("home.jsp");
        } else {
            response.sendRedirect("login.html");
        }
    }

    private boolean authenticate(String username, String password) {
        Connection conn = null;
        PreparedStatement stmt = null;
        ResultSet rs = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourDatabase", "user", "password");

            String sql = "SELECT * FROM users WHERE username=? AND password=?";
            stmt = conn.prepareStatement(sql);
            stmt.setString(1, username);
            stmt.setString(2, password);

            rs = stmt.executeQuery();

            return rs.next();
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
            return false;
        } finally {
            try {
                if (rs != null) rs.close();
                if (stmt != null) stmt.close();
                if (conn != null) conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
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
        Username: <input type="text" name="username"><br><br>
        Password: <input type="password" name="password"><br><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>



<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Home</title>
</head>
<body>
    <h1>Welcome, <%= session.getAttribute("user") %>!</h1>
    <a href="login.html">Logout</a>
</body>
</html>