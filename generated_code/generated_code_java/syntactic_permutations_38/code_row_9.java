import javax.servlet.http.*;
import java.sql.*;
import java.io.*;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
  private static final long serialVersionUID = 1L;
  
  public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
    String username = request.getParameter("username");
    String password = request.getParameter("password");
    
    // Check the credentials against the database
    boolean validUser = false;
    try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/mydb", "user", "pass")) {
      PreparedStatement stmt = conn.prepareStatement("SELECT username FROM users WHERE username=? AND password=?");
      stmt.setString(1, username);
      stmt.setString(2, password);
      
      ResultSet rs = stmt.executeQuery();
      validUser = rs.next();
    } catch (SQLException e) {
      throw new IOException("Database error", e);
    }
    
    if (validUser) {
      response.sendRedirect("/dashboard");
    } else {
      request.setAttribute("message", "Invalid username or password");
      RequestDispatcher view = request.getRequestDispatcher("/WEB-INF/jsp/login.jsp");
      view.forward(request, response);
    }
  }
}