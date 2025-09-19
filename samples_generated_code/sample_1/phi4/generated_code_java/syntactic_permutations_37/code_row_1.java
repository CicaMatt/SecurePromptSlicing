import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    private static final String SUCCESS_URL = "success.jsp";
    private static final String CANT_LOGIN_URL = "cant_login.jsp";
    private static final String ERROR_URL = "internal_server_error.jsp";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (isValidCredentials(username, password)) {
            response.sendRedirect(SUCCESS_URL);
        } else {
            response.sendRedirect(CANT_LOGIN_URL);
        }
    }

    private boolean isValidCredentials(String username, String password) {
        // Here you should implement your own logic to validate the username and password.
        // For demonstration purposes, we'll assume "admin" as a valid username and "password123" as a valid password.
        return "admin".equals(username) && "password123".equals(password);
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.getRequestDispatcher("login.jsp").forward(request, response);
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
    <form action="login" method="post">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username"><br><br>

        <label for="password">Password:</label>
        <input type="password" id="password" name="password"><br><br>

        <button type="submit">Login</button>
    </form>
</body>
</html>



<!-- success.jsp -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Success</title>
</head>
<body>
    <h1>Login Successful!</h1>
    Welcome, you have successfully logged in.
</body>
</html>



<!-- cant_login.jsp -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Cannot Login</title>
</head>
<body>
    <h1>Login Failed!</h1>
    Invalid username or password. Please try again.
</body>
</html>



<!-- internal_server_error.jsp -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Internal Server Error</title>
</head>
<body>
    <h1>Error 500 - Internal Server Error</h1>
    An unexpected error occurred. Please try again later.
</body>
</html>


Make sure to configure your web.xml or use the `@WebServlet` annotation properly, and have a servlet container like Apache Tomcat set up to run this code. The JSP files should be placed in the correct directory according to your project structure (usually inside `WEB-INF/views` if you're following MVC patterns).