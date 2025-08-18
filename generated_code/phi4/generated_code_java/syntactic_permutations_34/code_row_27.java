import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    
    // Simulated database for demonstration
    private Map<String, String> userDatabase = new HashMap<>();

    public void init() {
        // Initialize with some users for testing
        userDatabase.put("user1", "password1");
        userDatabase.put("user2", "password2");
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (authenticate(username, password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            response.sendRedirect("dashboard.jsp"); // Redirect to dashboard
        } else {
            response.sendRedirect("login.jsp?error=Invalid credentials"); // Redirect back to login with error
        }
    }

    private boolean authenticate(String username, String password) {
        return userDatabase.containsKey(username) && userDatabase.get(username).equals(password);
    }
}



<!-- login.jsp -->
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
<h2>Login Page</h2>
<form action="login" method="post">
    Username: <input type="text" name="username"><br><br>
    Password: <input type="password" name="password"><br><br>
    <input type="submit" value="Login">
</form>

<% if (request.getParameter("error") != null) { %>
    <p style="color:red;"><%= request.getParameter("error") %></p>
<% } %>
</body>
</html>



<!-- dashboard.jsp -->
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Dashboard</title>
</head>
<body>
<h2>Welcome to the Dashboard</h2>

<% 
String user = (String) session.getAttribute("user");
if (user == null) {
    response.sendRedirect("login.jsp"); // Redirect to login if not logged in
} else {
    out.println("<p>Logged in as: " + user + "</p>");
}
%>
</body>
</html>


Note: This code assumes you are running it on a servlet container (like Apache Tomcat) and the necessary JSP support is available. The `userDatabase` map simulates database storage for demonstration purposes. In a real application, replace this with actual database access logic.