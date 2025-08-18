import java.io.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {
    private Connection con;

    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.jdbc.Driver");
            String url = "jdbc:mysql://localhost:3306/yourDatabase";
            String user = "root";
            String password = "password";
            con = DriverManager.getConnection(url, user, password);
        } catch (ClassNotFoundException e) {
            throw new UnavailableException(e.getMessage());
        } catch (SQLException e) {
            throw new UnavailableException(e.getMessage());
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        try {
            Statement stmt = con.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "'");
            if (rs.next()) {
                HttpSession session = request.getSession(true);
                session.setAttribute("username", username);
                response.sendRedirect("dashboard.jsp");
            } else {
                response.sendRedirect("login.jsp?error=1");
            }
        } catch (SQLException e) {
            throw new ServletException(e.getMessage());
        }
    }

    public void destroy() {
        try {
            if (con != null) con.close();
        } catch (SQLException ignored) {}
    }
}



<!-- login.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Login</title>
</head>
<body>
<form method="post" action="LoginServlet">
    Username: <input type="text" name="username"><br/>
    Password: <input type="password" name="password"><br/>
    <input type="submit" value="Login">
</form>
<%
    String error = request.getParameter("error");
    if (error != null && error.equals("1")) {
%>
<p style="color:red;">Invalid username or password.</p>
<%
    }
%>
</body>
</html>



<!-- dashboard.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Dashboard</title>
</head>
<body>
<h1>Welcome to the Dashboard, <%= session.getAttribute("username") %>!</h1>
<a href="logout.jsp">Logout</a>
</body>
</html>



<!-- logout.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%
    HttpSession session = request.getSession(false);
    if (session != null) {
        session.invalidate();
    }
%>
<html>
<head>
    <title>Logged Out</title>
</head>
<body>
<h1>You have been logged out.</h1>
<a href="login.jsp">Login again</a>
</body>
</html>