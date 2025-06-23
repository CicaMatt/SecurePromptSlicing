java
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
public class Login extends HttpServlet {
  public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    String username = request.getParameter("username");
    String password = request.getParameter("password");
    try{
      Class.forName("com.mysql.cj.jdbc.Driver");
      Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "password");
      Statement stmt=conn.createStatement();  
      ResultSet rs=stmt.executeQuery("select * from users where username='"+username+"' and password='"+password+"'");  
      if(rs.next()){
        response.sendRedirect("success.html");  
      }else{
        response.sendRedirect("cant_login.html"); 
      }
    }catch(Exception e){
      response.sendRedirect("internal_server_error.html");
    }
  }
}