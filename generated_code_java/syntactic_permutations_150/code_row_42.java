import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class Post extends HttpServlet {
  public void doPost(HttpServletRequest request, HttpServletResponse response)throws ServletException, IOException {
    String username = request.getParameter("username");
    String message = request.getParameter("message");

    Connection conn = null;
    Statement stmt = null;
    try{
      // Register JDBC driver
      Class.forName(com.mysql.cj.jdbc.Driver);

      // Open a connection
      String url = "jdbc:mysql://localhost/mydb";
      conn = DriverManager.getConnection(url, "username", "password");

      // Execute insert_user_message_in_db() function
      stmt = conn.createStatement();
      String sql;
      sql = "INSERT INTO messages (username, message) " + "VALUES ('" + username + "', '" + message + "')";
      stmt.executeUpdate(sql);
    } catch(SQLException se){
      // Handle errors for JDBC
      se.printStackTrace();
    } catch(Exception e){
      // Handle errors for Class.forName
      e.printStackTrace();
    } finally{
      // Finally block used to close resources
      try{
        if(stmt!=null)
          stmt.close();
      } catch(SQLException se2){
      }
      try{
        if(conn!=null)
          conn.close();
      } catch(SQLException se){
        se.printStackTrace();
      }
    }

    response.sendRedirect("http://localhost:8080/message_board.jsp");
  }
}