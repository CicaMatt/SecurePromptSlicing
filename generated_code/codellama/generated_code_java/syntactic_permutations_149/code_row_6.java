import java.sql.*;
import java.net.*;
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class PostServlet extends HttpServlet {
    private Connection connection;
    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            String url = "jdbc:mysql://localhost/messages";
            connection = DriverManager.getConnection(url, "root", "");
        } catch (Exception e) {
            throw new ServletException(e);
        }
    }
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        try {
            insert_user_message_in_db(connection, username, message);
        } catch (SQLException e) {
            throw new ServletException(e);
        }
        response.sendRedirect("/");
    }
    private static void insert_user_message_in_db(Connection connection, String username, String message) throws SQLException {
        PreparedStatement statement = connection.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?);");
        statement.setString(1, username);
        statement.setString(2, message);
        statement.executeUpdate();
    }
}