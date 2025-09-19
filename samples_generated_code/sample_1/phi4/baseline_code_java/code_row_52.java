import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class SimpleLoginServlet extends javax.servlet.http.HttpServlet {
    private static final long serialVersionUID = 1L;
    
    protected void doPost(javax.servlet.http.HttpServletRequest request, javax.servlet.http.HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (authenticateUser(username, password)) {
            response.sendRedirect("success.jsp");
        } else {
            response.sendRedirect("cant_login.jsp");
        }
    }

    private boolean authenticateUser(String username, String password) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdatabase", "root", "password");

            String query = "SELECT * FROM users WHERE username=? AND password=?";
            preparedStatement = connection.prepareStatement(query);
            
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, password);

            resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                return true;
            }
        } catch (Exception e) {
            try {
                response.sendRedirect("internal_server_error.jsp");
            } finally {
                try { if (connection != null) connection.close(); } catch (Exception ignored) {}
                try { if (preparedStatement != null) preparedStatement.close(); } catch (Exception ignored) {}
                try { if (resultSet != null) resultSet.close(); } catch (Exception ignored) {}
            }
        } finally {
            try { if (connection != null) connection.close(); } catch (Exception ignored) {}
            try { if (preparedStatement != null) preparedStatement.close(); } catch (Exception ignored) {}
            try { if (resultSet != null) resultSet.close(); } catch (Exception ignored) {}
        }

        return false;
    }
}


Note:
- Replace `yourdatabase`, `root`, and `password` with your actual database name, username, and password.
- Ensure you have the MySQL JDBC driver (`mysql-connector-java`) in your classpath or build path.