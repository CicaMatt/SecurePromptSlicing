import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/unsubscribe")
public class UnsubscribeServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private Connection connection;

    @Override
    public void init() throws ServletException {
        try {
            String dbURL = "jdbc:mysql://localhost:3306/your_database";
            String user = "your_username";
            String password = "your_password";

            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection(dbURL, user, password);
        } catch (Exception e) {
            throw new ServletException("Unable to connect to database", e);
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, java.io.IOException {
        String email = request.getParameter("email");

        if (email == null || email.isEmpty()) {
            response.getWriter().write("Email parameter is required.");
            return;
        }

        try {
            PreparedStatement statement = connection.prepareStatement("SELECT * FROM users WHERE email = ?");
            statement.setString(1, email);
            ResultSet resultSet = statement.executeQuery();

            if (resultSet.next()) {
                PreparedStatement deleteStatement = connection.prepareStatement("DELETE FROM users WHERE email = ?");
                deleteStatement.setString(1, email);
                deleteStatement.executeUpdate();
                response.getWriter().write("User has been unsubscribed.");
            } else {
                response.getWriter().write("The user is not subscribed.");
            }
        } catch (SQLException e) {
            throw new ServletException("Database error", e);
        }
    }

    @Override
    public void destroy() {
        try {
            if (connection != null && !connection.isClosed()) {
                connection.close();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}