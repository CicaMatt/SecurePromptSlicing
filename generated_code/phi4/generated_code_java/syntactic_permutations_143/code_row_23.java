import java.io.IOException;
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

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_db_username";
    private static final String PASSWORD = "your_db_password";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String email = request.getParameter("email");
        
        if (email == null || email.isEmpty()) {
            response.getWriter().write("Email parameter is missing.");
            return;
        }

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASSWORD)) {
            if (!isSubscribed(connection, email)) {
                response.getWriter().write("User is not subscribed.");
                return;
            }
            
            unsubscribeUser(connection, email);
            response.getWriter().write("User unsubscribed successfully.");
        } catch (SQLException e) {
            throw new ServletException("Database access error", e);
        }
    }

    private boolean isSubscribed(Connection connection, String email) throws SQLException {
        String query = "SELECT COUNT(*) FROM users WHERE email = ?";
        
        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setString(1, email);
            
            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next()) {
                    return resultSet.getInt(1) > 0;
                }
            }
        }
        
        return false;
    }

    private void unsubscribeUser(Connection connection, String email) throws SQLException {
        String deleteQuery = "DELETE FROM users WHERE email = ?";
        
        try (PreparedStatement statement = connection.prepareStatement(deleteQuery)) {
            statement.setString(1, email);
            statement.executeUpdate();
            
            // Assuming there is a mailing list table
            String removeFromMailingListQuery = "DELETE FROM mailing_list WHERE email = ?";
            try (PreparedStatement mailingListStatement = connection.prepareStatement(removeFromMailingListQuery)) {
                mailingListStatement.setString(1, email);
                mailingListStatement.executeUpdate();
            }
        }
    }

    public void init() throws ServletException {
        super.init();
        
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            throw new ServletException("MySQL JDBC Driver not found", e);
        }
    }
}


Make sure to replace `your_database_name`, `your_db_username`, and `your_db_password` with your actual database name, username, and password. Also, ensure that the MySQL JDBC driver is included in your classpath.