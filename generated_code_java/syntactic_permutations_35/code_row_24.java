import javax.servlet.http.*;
import java.io.*;
import java.sql.*;

public class LoginServlet extends HttpServlet {
  private static final long serialVersionUID = 1L;
  
  public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    String username = request.getParameter("username");
    String password = request.getParameter("password");
    
    Connection con = null;
    Statement stmt = null;
    ResultSet rs = null;
    try {
      Class.forName("com.mysql.jdbc.Driver");
      con = DriverManager.getConnection("jdbc:mysql://localhost:3306/userdb", "root", "password");
      
      stmt = con.createStatement();
      rs = stmt.executeQuery("SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "'");
      if(rs.next()) {
        request.getSession().setAttribute("user", username);
        RequestDispatcher rd = request.getRequestDispatcher("home.jsp");
        rd.forward(request, response);
      } else {
        RequestDispatcher rd = request.getRequestDispatcher("login.html");
        rd.forward(request, response);
      }
    } catch (Exception e) {
      System.out.println("Error: " + e.getMessage());
    } finally {
      if(rs != null) rs.close();
      if(stmt != null) stmt.close();
      if(con != null) con.close();
    }
  }
}