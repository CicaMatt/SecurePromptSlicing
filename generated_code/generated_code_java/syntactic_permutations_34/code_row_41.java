import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class Login extends HttpServlet {
   public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
      String username = request.getParameter("username");
      String password = request.getParameter("password");
      if (validateUser(username, password)) {
         RequestDispatcher rd = request.getRequestDispatcher("dashboard.jsp");
         rd.forward(request, response);
      } else {
         response.sendRedirect("login.html");
      }
   }
   
   private boolean validateUser(String username, String password) throws ServletException {
      try {
         Class.forName("com.mysql.jdbc.Driver");
         Connection con = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "root");
         Statement stmt = con.createStatement();
         ResultSet rs = stmt.executeQuery("SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "'");
         if (rs.next()) {
            return true;
         }
      } catch (Exception e) {
         throw new ServletException(e);
      }
      return false;
   }
}

### Explanation:
The code imports the necessary packages for the application to run. The doPost method is implemented in the Login class which inherits from the HttpServlet class. This method gets the username and password entered by the user as parameters and checks if they exist in the database using the validateUser method. If it returns true, the user is logged in and redirected to the dashboard page. If it returns false, the user is redirected back to the login page. The validateUser method retrieves data from a MySQL database table called users where username and password are stored. It returns true if they match and false otherwise.