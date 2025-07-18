import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class Login extends HttpServlet {
  public void doPost(HttpServletRequest request, HttpServletResponse response)
      throws ServletException, IOException {
    // JDBC driver name and database URL
    String JDBC_DRIVER = "com.mysql.jdbc.Driver";
    String DB_URL = "jdbc:mysql://localhost/db_example";

    //  Database credentials
    String USER = "root";
    String PASS = "";
    
    PrintWriter out = response.getWriter();
    Connection conn = null;
    PreparedStatement pstmt = null;
    ResultSet rs = null;
    int checker = 0;
    
    try {
      //STEP 2: Register JDBC driver
      Class.forName(JDBC_DRIVER);

      // Open a connection
      conn = DriverManager.getConnection(DB_URL, USER, PASS);

      //STEP 4: Execute a query
      String sql = "SELECT * FROM users";
      pstmt = conn.prepareStatement(sql);
      rs = pstmt.executeQuery();
      
      if (rs.next()) {
        String email = request.getParameter("email");
        String password = request.getParameter("password");
        checker = 1;
      } else {
        out.println("<p>Sorry, your credentials are incorrect.</p>");
      }
      
    } catch (Exception e) {
      out.println("Exception: " + e);
    } finally {
      try {
        if (rs != null) {
          rs.close();
        }
        
        if(pstmt != null) {
          pstmt.close();
        }
        
        if(conn != null) {
          conn.close();
        }
        
      } catch (SQLException ex) {
        System.out.println("Exception: " + ex);
      }
    }
    
    out.println("<html>");
    out.println("<head>");
    out.println("<title>Login</title>");
    out.println("</head>");
    out.println("<body>");
    
    if (checker == 1) {
      String oldEmail = request.getParameter("old_email");
      String newEmail = request.getParameter("new_email");
      
      if (!oldEmail.equals(newEmail)) {
        out.println("<p>Your email has been successfully changed.</p>");
        
        try {
          //STEP 2: Register JDBC driver
          Class.forName(JDBC_DRIVER);

          // Open a connection
          conn = DriverManager.getConnection(DB_URL, USER, PASS);
          
          String sql = "UPDATE users SET email = ?";
          pstmt = conn.prepareStatement(sql);
          pstmt.setString(1, newEmail);
          rs = pstmt.executeQuery();
        } catch (Exception e) {
          out.println("Exception: " + e);
        } finally {
          try {
            if (rs != null) {
              rs.close();
            }
            
            if(pstmt != null) {
              pstmt.close();
            }
            
            if(conn != null) {
              conn.close();
            }
            
          } catch (SQLException ex) {
            System.out.println("Exception: " + ex);
          }
        }
      } else {
        out.println("<p>Your new email must be different from your old email.</p>");
      }
      
    } else {
      out.println("<form method='post' action=''>");
      out.println("Old Email: <input type='text' name='old_email' /><br><br>");
      out.println("New Email: <input type='text' name='new_email' /><br><br>");
      out.println("Confirm Password: <input type='password' name='confirm_pass' /><br><br>");
      out.println("<input type='submit' value='Submit' />");
    }
    
    out.println("</body>");
    out.println("</html>");
  }
}