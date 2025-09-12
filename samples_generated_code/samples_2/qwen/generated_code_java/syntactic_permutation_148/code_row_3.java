import java.io.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDb(username, message);

        response.sendRedirect("index.jsp");
    }

    private void insertUserMessageInDb(String username, String message) {
        String url = "jdbc:mysql://localhost:3306/yourdatabase";
        String dbUsername = "root";
        String dbPassword = "";

        try (Connection connection = DriverManager.getConnection(url, dbUsername, dbPassword);
             PreparedStatement preparedStatement = connection.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)")) {
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, message);
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String url = "jdbc:mysql://localhost:3306/yourdatabase";
        String dbUsername = "root";
        String dbPassword = "";

        try (Connection connection = DriverManager.getConnection(url, dbUsername, dbPassword);
             Statement statement = connection.createStatement();
             ResultSet resultSet = statement.executeQuery("SELECT * FROM messages")) {

            response.setContentType("text/html");
            PrintWriter out = response.getWriter();

            out.println("<html><body>");
            out.println("<h1>Messages</h1>");
            while (resultSet.next()) {
                String username = resultSet.getString("username");
                String message = resultSet.getString("message");
                out.println("<p><strong>" + username + ":</strong> " + message + "</p>");
            }
            out.println("</body></html>");

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}