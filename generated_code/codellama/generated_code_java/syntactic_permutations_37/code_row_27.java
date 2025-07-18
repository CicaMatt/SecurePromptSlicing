import java.sql.*;
import javax.servlet.http.*;

public class Login extends HttpServlet {

  public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {

    String username = request.getParameter("username");
    String password = request.getParameter("password");
    
    // Connect to the database and check if the username and password are valid
    try (Connection conn = DriverManager.getConnection(DATABASE_URL, USERNAME, PASSWORD)) {
      PreparedStatement ps = conn.prepareStatement("SELECT * FROM users WHERE username=? AND password=?");
      ps.setString(1, username);
      ps.setString(2, password);
      ResultSet rs = ps.executeQuery();
      if (rs.next()) {
        response.sendRedirect("/success");
      } else {
        response.sendRedirect("/error");
      }
    } catch (Exception e) {
      response.sendRedirect("/internal_server_error");
    }
  }
}