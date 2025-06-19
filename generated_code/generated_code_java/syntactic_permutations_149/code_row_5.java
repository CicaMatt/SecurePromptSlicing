import java.io.*;
import javax.servlet.http.*;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;
public class GetMessage extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String user = request.getParameter("username");
        String message = request.getParameter("message");
        insert_user_message_in_db(user, message);
        request.getRequestDispatcher("/").forward(request, response);
    }

    private void insert_user_message_in_db(String username, String message) {
        Connection conn = getConnection();
        try {
            PreparedStatement statement = conn.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)");
            statement.setString(1, username);
            statement.setString(2, message);
            statement.executeUpdate();
        } catch (SQLException e) {
            System.out.println("An error occurred while inserting user message in db");
            e.printStackTrace();
        } finally {
            try {
                conn.close();
            } catch (SQLException e) {
                System.out.println("An error occurred while closing connection");
                e.printStackTrace();
            }
        }
    }

    private Connection getConnection() throws SQLException, ClassNotFoundException {
        Class.forName("com.mysql.jdbc.Driver");
        return DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "password");
    }
}