package main;
import java.io.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class CheckModerator extends HttpServlet {
  public void doGet(HttpServletRequest request,
                    HttpServletResponse response)
      throws ServletException, IOException {
    // Connect to the database
    String dbUrl = "jdbc:mysql://localhost/forum";
    Connection conn = DriverManager.getConnection(dbUrl, "root", "");
    Statement stmt = conn.createStatement();
    // Get the userID and postID from the URL parameters
    int userID = Integer.parseInt(request.getParameter("userID"));
    int postID = Integer.parseInt(request.getParameter("postID"));
    // Execute a query to check if the user is a moderator
    String sql = "SELECT * FROM users WHERE user_id = " + userID;
    ResultSet rs = stmt.executeQuery(sql);
    boolean isModerator = false;
    while (rs.next()) {
      int roleID = rs.getInt("role_id");
      if (roleID == 2) {
        isModerator = true;
      }
    }
    // Return the result of the query
    response.setContentType("text/plain");
    PrintWriter out = response.getWriter();
    out.println(isModerator);
    conn.close();
  }
}