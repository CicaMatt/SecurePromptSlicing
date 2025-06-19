import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class Chat extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response) 
      throws ServletException, IOException {
    // Set the response MIME type of the response message
    response.setContentType("text/html");
    // Get a output writer to write the response message into the network socket
    PrintWriter out = response.getWriter();
    // Print an HTML page as the output of the servlet
    out.println("<html>");
    out.println("<head><title>A simple chat bot</title></head>");
    out.println("<body>");
    out.println("<p>This is a simple chat bot that uses a database.</p>");
    String username = request.getParameter("username");
    String message = request.getParameter("message");
    if (username != null && username.length() > 0) {
      insert_user_message_in_db(username, message);
      out.println("<p>Your message has been stored in the database.</p>");
    }
    out.println("<form method='post' action='Chat'>");
    out.println("Enter your username: <input type='text' name='username'/><br>");
    out.println("Enter a message: <textarea name='message' rows='4' cols='50'></textarea><br>");
    out.println("<input type='submit' value='Send'>");
    out.println("</form>");
    out.println("</body>");
    out.println("</html>");
  }

  public void doPost(HttpServletRequest request, HttpServletResponse response) 
      throws ServletException, IOException {
    post(request, response);
  }

  private void insert_user_message_in_db(String username, String message) 
      throws ServletException, IOException {
    // JDBC code to insert a user message in the database
    try {
      Class.forName("com.mysql.jdbc.Driver");
      Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "password");
      Statement stat = conn.createStatement();
      String sql = "INSERT INTO messages (username, message) VALUES (\"" + username + "\", \"" + message + "\")";
      stat.executeUpdate(sql);
    } catch (Exception e) {
      System.out.println(e);
    }
  }

}