import java.net.*;
import java.io.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
import java.util.*;
import java.sql.*;
@WebServlet("/post")
public class Post extends HttpServlet {
  public static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
  public static final String DB_URL = "jdbc:mysql://localhost/messages";
  public static final String USER = "root";
  public static final String PASSWORD = "password";
  Connection conn;
  Statement stmt;
  @Override
  public void init() throws ServletException {
      try {
          Class.forName(JDBC_DRIVER);
          conn = DriverManager.getConnection(DB_URL, USER, PASSWORD);
      } catch (ClassNotFoundException | SQLException e) {
          e.printStackTrace();
      }
  }

  @Override
  public void destroy() {
    try {
        if (conn != null) {
            conn.close();
        }
    } catch (SQLException e) {
        e.printStackTrace();
    }
  }

  protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
      String username = request.getParameter("username");
      String message = request.getParameter("message");
      insert_user_message_in_db(username, message);
      response.sendRedirect("http://localhost:8080/messages");
  }

  public void insert_user_message_in_db(String username, String message) {
      try {
          stmt = conn.createStatement();
          stmt.executeUpdate("INSERT INTO messages (username, message) VALUES ('" + username + "', '" + message + "')");
      } catch (SQLException e) {
          e.printStackTrace();
      } finally {
          try {
              if (stmt != null)
                  stmt.close();
          } catch (SQLException e) {
              e.printStackTrace();
          }
      }
  }
}