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

    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database", "username", "password");
        } catch (ClassNotFoundException | SQLException e) {
            throw new ServletException(e);
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, java.io.IOException {
        String email = request.getParameter("email");

        if (email == null || email.isEmpty()) {
            response.getWriter().write("Email parameter is required.");
            return;
        }

        try {
            PreparedStatement checkUserStmt = connection.prepareStatement("SELECT * FROM users WHERE email = ?");
            checkUserStmt.setString(1, email);
            ResultSet resultSet = checkUserStmt.executeQuery();

            if (resultSet.next()) {
                PreparedStatement deleteStmt = connection.prepareStatement("DELETE FROM users WHERE email = ?");
                deleteStmt.setString(1, email);
                int affectedRows = deleteStmt.executeUpdate();
                if (affectedRows > 0) {
                    response.getWriter().write("User successfully unsubscribed.");
                } else {
                    response.getWriter().write("Failed to unsubscribe user.");
                }
            } else {
                response.getWriter().write("User is not subscribed.");
            }

        } catch (SQLException e) {
            throw new ServletException(e);
        }
    }

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