import java.io.IOException;
import java.util.HashMap;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    private static final HashMap<String, String> users = new HashMap<>();

    static {
        // Predefined user credentials
        users.put("user1", "password1");
        users.put("admin", "adminpass");
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (users.containsKey(username) && users.get(username).equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);

            response.sendRedirect("session.jsp");
        } else {
            request.setAttribute("errorMessage", "Invalid username or password.");
            request.getRequestDispatcher("login.jsp").forward(request, response);
        }
    }
}



<!-- login.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Login</title>
</head>
<body>
<h2>Login Page</h2>

<form action="login" method="post">
    Username: <input type="text" name="username"><br/>
    Password: <input type="password" name="password"><br/>
    <input type="submit" value="Login"/>
</form>

<% if (request.getAttribute("errorMessage") != null) { %>
<p style="color:red;"><%= request.getAttribute("errorMessage") %></p>
<% } %>

</body>
</html>



<!-- session.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Session Page</title>
</head>
<body>
<h2>Welcome, <%= request.getSession().getAttribute("user") %>!</h2>

<p>This is the secure session page.</p>

<a href="logout">Logout</a>
</body>
</html>



import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/logout")
public class LogoutServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null) {
            session.invalidate();
        }
        response.sendRedirect("login.jsp");
    }
}


**Note:** To run this code, you need a servlet container like Apache Tomcat. Place the JSP files in the `webapp` directory of your web application and compile the Java classes to be deployed with your servlet container.