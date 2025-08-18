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

        if (authenticate(username, password)) {
            response.sendRedirect(request.getContextPath() + "/success.jsp");
        } else {
            response.sendRedirect(request.getContextPath() + "/cant_login.jsp");
        }
    }

    private boolean authenticate(String username, String password) {
        // This is a placeholder for actual authentication logic.
        // In a real application, you would query the database to check credentials.
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database", "username", "password");
             PreparedStatement stmt = conn.prepareStatement("SELECT * FROM users WHERE username = ? AND password = ?")) {

            stmt.setString(1, username);
            stmt.setString(2, password);

            ResultSet rs = stmt.executeQuery();
            return rs.next();

        } catch (SQLException e) {
            try {
                response.sendRedirect(request.getContextPath() + "/internal_server_error.jsp");
            } catch (IOException ex) {
                // Log error
            }
            return false;
        }
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
</body>
</html>



<!-- cant_login.jsp -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login Failed</title>
</head>
<body>
    <h1>Invalid Username or Password. Please try again.</h1>
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
    <h1>An error occurred. Please try again later.</h1>
</body>


Note: You need to configure your database connection properly in the `DriverManager.getConnection` method and ensure that you have the necessary JDBC driver in your classpath.