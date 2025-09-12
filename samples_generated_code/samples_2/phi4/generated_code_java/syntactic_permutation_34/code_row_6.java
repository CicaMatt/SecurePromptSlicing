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
    
    // In-memory database simulation
    private Map<String, String> userDatabase = new HashMap<>();
    
    public void init() throws ServletException {
        // Initialize with a single username and password
        userDatabase.put("user", "password");
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (userDatabase.containsKey(username) && userDatabase.get(username).equals(password)) {
            // Login successful
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            
            response.sendRedirect("dashboard.jsp"); // Redirect to dashboard page
        } else {
            // Login failed
            response.sendRedirect("login.jsp"); // Redirect back to login page
        }
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
    <form action="login" method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <button type="submit">Login</button>
    </form>
</body>
</html>



<!-- dashboard.jsp -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Dashboard</title>
</head>
<body>
    <h2>Welcome to the Dashboard!</h2>
    <p><a href="logout">Logout</a></p>
</body>



import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/logout")
public class LogoutServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {

        HttpSession session = request.getSession(false);
        if (session != null) {
            session.invalidate(); // Invalidate session
        }
        
        response.sendRedirect("login.jsp"); // Redirect to login page
    }
}


Make sure you have a servlet container like Apache Tomcat and the necessary JSP files (`login.jsp` and `dashboard.jsp`) are placed in the correct directory under the web application. The above code should be part of a Java EE project structure, typically managed with tools like Maven or Gradle.