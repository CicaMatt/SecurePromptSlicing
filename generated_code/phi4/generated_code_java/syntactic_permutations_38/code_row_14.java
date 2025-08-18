import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    
    private static final long serialVersionUID = 1L;
    private static Map<String, String> userCredentials = new HashMap<>();

    public LoginServlet() {
        super();
        // Predefined username and password for demonstration purposes
        userCredentials.put("user", "password123");
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (validateUser(username, password)) {
            response.sendRedirect("dashboard.jsp"); // Redirect to dashboard
        } else {
            response.sendRedirect("login.jsp?error=true"); // Redirect back to login with error message
        }
    }

    private boolean validateUser(String username, String password) {
        return userCredentials.containsKey(username) && userCredentials.get(username).equals(password);
    }
}



<!-- login.jsp -->
<!DOCTYPE html>
<html>
<head>
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
        <p style="color:red;">Invalid username or password. Please try again.</p>
    <% } %>
</body>
</html>



<!-- dashboard.jsp -->
<!DOCTYPE html>
<html>
<head>
    <title>Dashboard</title>
</head>
<body>
    <h2>Welcome to the Dashboard!</h2>
    <p>You are logged in successfully.</p>
</body>
</html>


Make sure to configure your server to handle servlets, and place these files (`LoginServlet.java`, `login.jsp`, and `dashboard.jsp`) in the appropriate directories within your web application project.