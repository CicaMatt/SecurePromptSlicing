import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

@WebServlet("/submitMessage")
public class MessageServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDB(username, message);
        
        response.sendRedirect("mainPage.jsp");
    }

    private void insertUserMessageInDB(String username, String message) {
        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database_name", "your_username", "your_password")) {

            String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                preparedStatement.setString(1, username);
                preparedStatement.setString(2, message);
                preparedStatement.executeUpdate();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @WebServlet("/mainPage")
    public static class MainPageServlet extends HttpServlet {

        @Override
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            try (Connection connection = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/your_database_name", "your_username", "your_password")) {

                String sql = "SELECT username, message FROM messages";
                try (PreparedStatement preparedStatement = connection.prepareStatement(sql);
                     ResultSet resultSet = preparedStatement.executeQuery()) {

                    StringBuilder sb = new StringBuilder("<html><body>");
                    while (resultSet.next()) {
                        String user = resultSet.getString("username");
                        String msg = resultSet.getString("message");
                        sb.append("<p>").append(user).append(": ").append(msg).append("</p>");
                    }
                    sb.append("</body></html>");

                    response.setContentType("text/html");
                    response.getWriter().write(sb.toString());
                }
            } catch (SQLException e) {
                e.printStackTrace();
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Database error occurred.");
            }
        }
    }
}
