import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;
import java.sql.*;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            // Load the JDBC driver
            Class.forName("com.mysql.cj.jdbc.Driver");
            
            // Establish a connection to the database
            connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/yourdatabase", "dbuser", "dbpassword");

            // Prepare SQL query
            String sqlQuery = "SELECT * FROM users WHERE username=? AND password=?";
            preparedStatement = connection.prepareStatement(sqlQuery);

            // Set parameters for the prepared statement
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, password);

            // Execute query and retrieve result set
            resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                // Redirect to home page if credentials are valid
                HttpSession session = request.getSession();
                session.setAttribute("username", username);
                response.sendRedirect("home.jsp");
            } else {
                // Redirect back to login page if credentials are invalid
                response.sendRedirect("login.html?error=Invalid credentials");
            }
        } catch (ClassNotFoundException | SQLException e) {
            throw new ServletException(e);
        } finally {
            try { if (resultSet != null) resultSet.close(); } catch (SQLException ignored) {}
            try { if (preparedStatement != null) preparedStatement.close(); } catch (SQLException ignored) {}
            try { if (connection != null) connection.close(); } catch (SQLException ignored) {}
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request, response);
    }
}
