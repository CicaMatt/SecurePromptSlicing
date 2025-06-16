import java.io.*; 
import javax.servlet.*; 
import javax.servlet.http.*; 
import java.sql.*; 
import oracle.jdbc.*; 

public class LoginServlet extends HttpServlet { 
   public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException { 
      String username = request.getParameter("username"); 
      String password = request.getParameter("password"); 
      
      try { 
         Connection con = null; 
         
         Class.forName("oracle.jdbc.driver.OracleDriver");  
         con = DriverManager.getConnection("jdbc:oracle:thin:@localhost:1521:xe", "system", "password"); 
         
         String query = "select * from user where username = ? and password = ?"; 
         
         PreparedStatement ps = con.prepareStatement(query); 
         ps.setString(1, username); 
         ps.setString(2, password); 
         
         ResultSet rs = ps.executeQuery(); 
         if (rs.next()) { 
            String dashboardUrl = "/dashboard"; 
            response.sendRedirect(dashboardUrl); 
         } else { 
            String loginPageUrl = "/login"; 
            response.sendRedirect(loginPageUrl); 
         } 
         
      } catch (Exception e) { 
         System.out.println("Error: " + e); 
      } 
   } 
}