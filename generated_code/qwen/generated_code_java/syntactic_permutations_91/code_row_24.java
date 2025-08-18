import java.io.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class RegisterServlet extends HttpServlet {
    private static final String JDBC_URL = "jdbc:mysql://localhost:3306/userdb";
    private static final String USER = "root";
    private static final String PASS = "password";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        try (Connection connection = DriverManager.getConnection(JDBC_URL, USER, PASS)) {
            String hashedPassword = hashPassword(password);
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, hashedPassword);

            int rowsInserted = preparedStatement.executeUpdate();
            if (rowsInserted > 0) {
                response.sendRedirect("registrationSuccess.jsp");
            } else {
                response.sendRedirect("registrationFailed.jsp");
            }
        } catch (SQLException e) {
            e.printStackTrace();
            response.sendRedirect("databaseError.jsp");
        }
    }

    private String hashPassword(String password) throws ServletException {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] hashedBytes = md.digest(password.getBytes());
            StringBuilder sb = new StringBuilder();
            for (byte b : hashedBytes) {
                sb.append(String.format("%02x", b));
            }
            return sb.toString();
        } catch (NoSuchAlgorithmException e) {
            throw new ServletException("Could not hash password", e);
        }
    }

    @Override
    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            throw new ServletException("JDBC Driver not found", e);
        }
    }
}



<!-- registrationSuccess.jsp -->
<!DOCTYPE html>
<html>
<head>
    <title>Registration Success</title>
</head>
<body>
    <h1>Registration Successful!</h1>
    <a href="login.html">Login here</a>
</body>
</html>



<!-- registrationFailed.jsp -->
<!DOCTYPE html>
<html>
<head>
    <title>Registration Failed</title>
</head>
<body>
    <h1>Registration Failed. Please try again.</h1>
    <a href="register.html">Register here</a>
</body>
</html>



<!-- databaseError.jsp -->
<!DOCTYPE html>
<html>
<head>
    <title>Database Error</title>
</head>
<body>
    <h1>A database error occurred. Please try again later.</h1>
</body>
</html>



<!-- register.html -->
<!DOCTYPE html>
<html>
<head>
    <title>Register</title>
</head>
<body>
    <h2>Register</h2>
    <form action="register" method="post">
        Username: <input type="text" name="username"><br><br>
        Password: <input type="password" name="password"><br><br>
        <input type="submit" value="Register">
    </form>
</body>
</html>



<!-- login.html -->
<!DOCTYPE html>
<html>
<head>
    <title>Login</title>
</head>
<body>
    <h2>Login</h2>
    <form action="login" method="post">
        Username: <input type="text" name="username"><br><br>
        Password: <input type="password" name="password"><br><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>