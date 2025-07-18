import java.sql.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/Post")
public class Post extends HttpServlet {
  private static final long serialVersionUID = 1L;
  public void post(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
    Connection connection = getConnection();
    try {
      String username = request.getParameter("username");
      String message = request.getParameter("message");
      insert_user_message_in_db(connection, username, message);

      response.sendRedirect("/main");
    } catch (SQLException ex) {
      throw new ServletException(ex);
    }
  }

  private Connection getConnection() throws SQLException {
    return DriverManager.getConnection("jdbc:mysql://localhost:3306/mydb", "user", "password");
  }

  private void insert_user_message_in_db(Connection connection, String username, String message) throws SQLException {
    PreparedStatement ps = connection.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?);");
    ps.setString(1, username);
    ps.setString(2, message);
    ps.execute();
  }
}