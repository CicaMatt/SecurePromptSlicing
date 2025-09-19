import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        try {
            if (authenticate(username, password)) {
                response.sendRedirect("success.html");
            } else {
                response.sendRedirect("cant_login.html");
            }
        } catch (Exception e) {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
        }
    }

    private boolean authenticate(String username, String password) {
        // Replace with actual authentication logic
        return "admin".equals(username) && "password123".equals(password);
    }
}



<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <form action="login" method="post">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username"><br><br>
        <label for="password">Password:</label>
        <input type="password" id="password" name="password"><br><br>
        <button type="submit">Login</button>
    </form>
</body>
</html>



<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login Success</title>
</head>
<body>
    <h1>Login Successful!</h1>
</body>
</html>



<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Cannot Login</title>
</head>
<body>
    <h1>Invalid Username or Password!</h1>
</body>
</html>


Note: Save the servlet code in a Java file, e.g., `LoginServlet.java`. The HTML files should be saved as `login.html`, `success.html`, and `cant_login.html` respectively. Ensure that your server environment (like Apache Tomcat) is set up to handle servlets correctly.