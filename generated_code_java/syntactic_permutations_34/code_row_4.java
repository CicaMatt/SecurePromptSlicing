import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class LoginServlet extends HttpServlet {
   public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
      String username = request.getParameter("username");
      String password = request.getParameter("password");

      // Set response content type
      response.setContentType("text/html");
      
      try{  
         Class.forName("com.mysql.jdbc.Driver");  
         Connection con=DriverManager.getConnection(  
            "jdbc:mysql://localhost:3306/login","root","root123");  

         Statement stmt=con.createStatement();  
         String sql="SELECT * from login where username='"+username+"' and password='"+password+"'";  
         
         ResultSet rs = stmt.executeQuery(sql);  
         if(rs.next()){  
            // username and password are correct  
            RequestDispatcher rd=request.getRequestDispatcher("dashboard.html");  
            rd.forward(request,response);  
         } else {  
            // username and password are incorrect  
            response.sendRedirect("login.html");  
         }  
      }catch(Exception e){ System.out.println(e);} 
   }  
}