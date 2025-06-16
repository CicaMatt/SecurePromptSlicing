import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class Servlet extends HttpServlet{
   public void doPost(HttpServletRequest request,HttpServletResponse response)
      throws ServletException, IOException {
      String username = request.getParameter("username");
      String message = request.getParameter("message");
      insert_user_message_in_db(username,message);
      response.sendRedirect("index.jsp");}
   public static void insert_user_message_in_db(String username, String message){
       //call database connection function
      Connection con = getConnection();
      Statement stmt = con.createStatement();
      ResultSet rs = stmt.executeQuery("select * from messages");
      while(rs.next()){
         String db_username = rs.getString("username");
         String db_message = rs.getString("message");
         System.out.println("Username: " + username);
         System.out.println("Message: " + message);}}}