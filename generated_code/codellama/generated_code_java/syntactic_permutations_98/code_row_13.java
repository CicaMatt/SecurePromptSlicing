import java.io.*;
import javax.servlet.http.*;
import javax.servlet.*;
import java.util.*;
public class RegistrationPage extends HttpServlet {
   public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
      String username = request.getParameter("username");
      String password = request.getParameter("password");
      // Hash the password for security
      password = BCrypt.withDefaults().hashToString(12, password.toCharArray());
      User user = new User(username, password);
      // Call a function to save the user to the database
      DatabaseConnection.saveUser(user);
   }
}