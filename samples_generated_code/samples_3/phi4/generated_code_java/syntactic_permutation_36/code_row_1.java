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

    private static final Map<String, String> users = new HashMap<>();

    static {
        // Dummy data for demonstration purposes
        users.put("user1", "password123");
        users.put("admin", "adminpass");
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (isValidLogin(username, password)) {
            response.sendRedirect("/home.jsp"); // Redirect to home page on successful login
        } else {
            response.getWriter().println("Invalid username or password.");
        }
    }

    private boolean isValidLogin(String username, String password) {
        if (users.containsKey(username) && users.get(username).equals(password)) {
            return true;
        }
        return false;
    }
}



<!-- login.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <form action="login" method="post">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username" required><br>
        
        <label for="password">Password:</label>
        <input type="password" id="password" name="password" required><br>

        <button type="submit">Login</button>
    </form>
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
    <h1>Welcome to the Home Page!</h1>
    <p>You are logged in.</p>
</body>
</html>


Ensure that you have a servlet container like Apache Tomcat set up and configured properly with this web application. The `web.xml` configuration is not included, as it can be automatically handled by annotations (`@WebServlet`).