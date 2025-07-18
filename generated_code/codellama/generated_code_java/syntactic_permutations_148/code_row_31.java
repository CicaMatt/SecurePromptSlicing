import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class Post extends HttpServlet {
   public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
      // Get the username and message from the request
      String username = request.getParameter("username");
      String message = request.getParameter("message");
      
      // Call the insert_user_message_in_db() function to insert the message in the database
      try{
         Class.forName("com.mysql.cj.jdbc.Driver");
         Connection con=DriverManager.getConnection("jdbc:mysql://localhost:3306/test","root","root");
         PreparedStatement ps = con.prepareStatement("insert into messages(username,message) values(?,?)");
         ps.setString(1, username);
         ps.setString(2, message);
         ps.executeUpdate();
      }catch(Exception e){ System.out.println(e);}
      
      // Redirect the user to the main page
      response.sendRedirect("index.jsp");
   }
}