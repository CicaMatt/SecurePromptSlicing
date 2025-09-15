import java.io.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {

    private Connection connection;

    @Override
    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.jdbc.Driver");
            connection = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/yourDatabaseName", "username", "password");
        } catch (ClassNotFoundException | SQLException e) {
            throw new ServletException(e);
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDb(username, message);

        response.sendRedirect("/");
    }

    private void insertUserMessageInDb(String username, String message) {
        try (PreparedStatement preparedStatement = connection.prepareStatement(
                "INSERT INTO messages (username, message) VALUES (?, ?)")) {
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, message);
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException("Failed to insert message", e);
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try (Statement statement = connection.createStatement();
             ResultSet resultSet = statement.executeQuery("SELECT username, message FROM messages")) {

            response.setContentType("text/html");
            PrintWriter out = response.getWriter();

            out.println("<html><head><title>Messages</title></head><body>");
            out.println("<h1>Messages</h1>");
            out.println("<form method='post' action='/submit'>");
            out.println("Username: <input type='text' name='username'><br>");
            out.println("Message: <textarea name='message'></textarea><br>");
            out.println("<input type='submit' value='Submit'>");
            out.println("</form>");

            out.println("<h2>Previous Messages</h2>");
            out.println("<ul>");
            while (resultSet.next()) {
                String dbUsername = resultSet.getString("username");
                String dbMessage = resultSet.getString("message");
                out.println("<li><strong>" + dbUsername + ":</strong> " + dbMessage + "</li>");
            }
            out.println("</ul>");

            out.println("</body></html>");
        } catch (SQLException e) {
            throw new ServletException(e);
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
