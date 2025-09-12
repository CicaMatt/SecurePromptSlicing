import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class LoginPageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        boolean isValidUser = checkLogin(username, password);

        if (isValidUser) {
            // Redirect to a welcome page
            response.sendRedirect("welcome.jsp");
        } else {
            // Redirect back to the login page with an error message
            RequestDispatcher rd = request.getRequestDispatcher("login.jsp");
            request.setAttribute("message", "Invalid username or password. Please try again.");
            rd.forward(request, response);
        }
    }

    private boolean checkLogin(String username, String password) {
        String jdbcURL = "jdbc:mysql://localhost:3306/mydb";
        String dbUser = "root";
        String dbPassword = "password";

        Connection connection = null;
        PreparedStatement statement = null;
        ResultSet resultSet = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection(jdbcURL, dbUser, dbPassword);

            String sql = "SELECT * FROM users WHERE username=? AND password=?";
            statement = connection.prepareStatement(sql);
            statement.setString(1, username);
            statement.setString(2, password);

            resultSet = statement.executeQuery();
            return resultSet.next();

        } catch (SQLException | ClassNotFoundException e) {
            e.printStackTrace();
        } finally {
            try {
                if (resultSet != null) resultSet.close();
                if (statement != null) statement.close();
                if (connection != null) connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return false;
    }
}