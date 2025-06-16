import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import com.mysql.jdbc.exceptions.jdbc4.CommunicationsException;
 
public class ChatApp extends HttpServlet{
    // JDBC driver name and database URL
   static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";
   static final String DB_URL = "jdbc:mysql://localhost/chat";

   //  Database credentials
   static final String USER = "username";
   static final String PASS = "password";
   
   private Connection conn;
   private Statement stmt;
   
   public void init() throws ServletException{
      // Register JDBC driver
      try {
         Class.forName(JDBC_DRIVER);
      } catch (ClassNotFoundException e) {
         System.out.println("JDBC Driver not found");
         return;
      }
   
      // Open a connection
      conn = null;
      try {
         conn = DriverManager.getConnection(DB_URL,USER,PASS);
      } catch (SQLException e) {
         System.out.println("Connection failed");
         return;
      }
   }
   
   public void destroy(){
      // Close the connection
      try {
         conn.close();
      } catch (SQLException e){
         System.out.println("Error closing connection");
      }
   } 
   
   protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
      String username = request.getParameter("username");
      String message = request.getParameter("message");
      
      // Insert the message into the database
      try {
         stmt = conn.createStatement();
         String sql;
         sql = "INSERT INTO messages (username, message) VALUES ('" + username + "','" + message + "')";
         stmt.executeUpdate(sql);
         System.out.println("Message successfully inserted into database");
      } catch (SQLException e){
         System.out.println("Error inserting message into database: " + e.getMessage());
      }
      
      // Redirect the user to the main page
      response.sendRedirect("chat.html");
   }   
}