import java.io.*;
import java.sql.*;
import javax.servlet.http.*;

public class LoginPage extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/loginpage", "admin", "admin")){
            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery("SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "'");

            if (resultSet.next()) {
                response.sendRedirect("/success.html");
            } else {
                response.sendRedirect("/cant_login.html");
            }
        } catch (SQLException e) {
            response.sendRedirect("internal_server_error.html");
        }
    }
}