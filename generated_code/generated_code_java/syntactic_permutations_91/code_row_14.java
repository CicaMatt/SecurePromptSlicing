import javax.servlet.http.*;
import java.sql.*;
import com.mysql.jdbc.Driver;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
  
public class RegisterServlet extends HttpServlet {
   public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
      // Get the username and password
      String username = request.getParameter("username");
      String password = request.getParameter("password");
  
      // Connect to the database
      Connection con = DriverManager.getConnection("jdbc:mysql://localhost/mydatabase", "user", "password");
  
      try {
         PreparedStatement statement = con.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)");
         statement.setString(1, username);
         statement.setString(2, hashPassword(password));
         statement.executeUpdate();
      } catch (SQLException e) {
         throw new ServletException("Error inserting user", e);
      }
  
      response.getWriter().println("User inserted successfully");
   }
  
   private String hashPassword(String password) throws NoSuchAlgorithmException {
      MessageDigest digest = MessageDigest.getInstance("SHA-256");
      byte[] encodedhash = digest.digest(password.getBytes());
      return new String(encodedhash);
   }
}