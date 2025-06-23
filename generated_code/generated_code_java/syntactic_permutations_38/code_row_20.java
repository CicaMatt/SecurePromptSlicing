import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class Login extends HttpServlet {
  public void doPost(HttpServletRequest request, HttpServletResponse response)
      throws ServletException, IOException {
    response.setContentType("text/html");
    PrintWriter out = response.getWriter();

    String username = request.getParameter("username");
    String password = request.getParameter("password");

    String url = "jdbc:mysql://localhost:3306/";
    Connection conn = null;
    Statement stmt = null;
    try {
      Class.forName("com.mysql.cj.jdbc.Driver");
      conn = DriverManager.getConnection(url, "root", "password");
      stmt = conn.createStatement();
      String sql = "SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "'";
      ResultSet rs = stmt.executeQuery(sql);
      if (rs.next()) {
        RequestDispatcher rd = request.getRequestDispatcher("/dashboard");
        rd.forward(request, response);
      } else {
        out.println("Incorrect username or password.");
        RequestDispatcher rd = request.getRequestDispatcher("/login");
        rd.include(request, response);
      }
    } catch (Exception e) {
      out.println("error: " + e.getMessage());
    } finally {
      if (stmt != null) {
        try {
          stmt.close();
        } catch (SQLException e) {
          ;
        }
      }
      if (conn != null) {
        try {
          conn.close();
        } catch (SQLException e) {
          ;
        }
      }
    }
  }
}