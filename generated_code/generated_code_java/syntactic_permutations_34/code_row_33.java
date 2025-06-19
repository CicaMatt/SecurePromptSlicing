import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class LogPageServlet extends HttpServlet {
  @Override
  public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
    // Set the content type
    response.setContentType("text/html");
    
    // Get the print writer
    PrintWriter pw = response.getWriter();
    
    String username = request.getParameter("username");
    String password = request.getParameter("password");
    if (username == null || password == null) {
      pw.println("<h2>Invalid user name or password</h2>");
      RequestDispatcher rd = request.getRequestDispatcher("/login.html");
      rd.include(request, response);
    } else {
      String dbUrl = "jdbc:mysql://localhost/mydb";
      Connection conn;
      try {
        Class.forName("com.mysql.jdbc.Driver");
        conn = DriverManager.getConnection(dbUrl, "root", "password");
        
        // Check if the username and password are in the database
        Statement stmt = conn.createStatement();
        ResultSet rs = stmt.executeQuery("SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "'");
        
        if (rs.next()) {
          // If yes, redirect to dashboard page
          RequestDispatcher rd = request.getRequestDispatcher("/dashboard.html");
          rd.forward(request, response);
        } else {
          pw.println("<h2>Invalid user name or password</h2>");
          RequestDispatcher rd = request.getRequestDispatcher("/login.html");
          rd.include(request, response);
        }
        
      } catch (Exception e) {
        pw.println("Unable to connect to database.");
        e.printStackTrace();
      }
    }
  }
}