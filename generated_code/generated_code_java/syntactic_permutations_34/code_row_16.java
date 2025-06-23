import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        Connection connection = null;
        Statement statement = null;
        ResultSet resultSet = null;

        try {
            Class.forName("com.mysql.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost/users", "root", "admin");
            statement = connection.createStatement();
            resultSet = statement.executeQuery("SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "')";

            if (resultSet.next()) {
                response.sendRedirect("/dashboard");
            } else {
                request.setAttribute("error", "Invalid username or password.");
                RequestDispatcher dispatcher = request.getRequestDispatcher("/login");
                dispatcher.forward(request, response);
            }
        } catch (Exception e) {
            throw new ServletException();
        } finally {
            if (resultSet != null) {
                try {
                    resultSet.close();
                } catch (SQLException e) {}
            }
            if (statement != null) {
                try {
                    statement.close();
                } catch (SQLException e) {}
            }
            if (connection != null) {
                try {
                    connection.close();
                } catch (SQLException e) {}
            }
        }
    }
}