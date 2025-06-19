import java.io.*;
import javax.servlet.http.*;
import java.sql.*;

public class LoginServlet extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
    // Set response content type
    response.setContentType("text/html");

    PrintWriter out = response.getWriter();
    String title = "Login Page";

    String docType = "<!DOCTYPE html public \"-//W3C//DTD HTML 4.0 " + "Transitional//EN\">\n";
    out.println(docType + "<html>\n" + "<head><title>" + title + "</title></head>\n" + "<body bgcolor=\"#fdf5e6\">\n" + "<h1 align=\"center\">" + title + "</h1>\n" +
      "<form action=\"validate\" method=\"post\">\n" + "  <table border=\"0\" align=\"center\">\n" + "    <tr>\n" + "      <td>Username:</td>\n" + "      <td><input type=\"text\" name=\"username\" size=\"50\"></td>\n" + "    </tr>\n" +
      "    <tr>\n" + "      <td>Password:</td>\n" + "      <td><input type=\"password\" name=\"password\" size=\"50\"></td>\n" + "    </tr>\n" + "    <tr>\n" + "      <td colspan=\"2\" align=\"center\"><input type=\"submit\" value=\"Login\"></td>\n" +
      "    </tr>\n" + "  </table>\n" + "</form>\n");
    Connection conn = null;
    PreparedStatement pstmt = null;
    ResultSet rs = null;
    String url = "jdbc:mysql://localhost:3306/";
    String dbName = "web_customer_tracker";
    String driver = "com.mysql.cj.jdbc.Driver";
    String userName = "root";
    String password = "password";
    try {
      Class.forName(driver).newInstance();
      conn = DriverManager.getConnection(url + dbName, userName, password);
      String sql = "SELECT * FROM customers WHERE username=? AND password=?";
      pstmt = conn.prepareStatement(sql);
      String username = request.getParameter("username");
      String password = request.getParameter("password");
      pstmt.setString(1, username);
      pstmt.setString(2, password);
      rs = pstmt.executeQuery();
      if (rs.next()) {
        HttpSession session = request.getSession();
        session.setAttribute("authenticatedUser", username);
        response.sendRedirect("dashboard");
      } else {
        out.println("<p align=\"center\">Sorry, username and password are invalid.</p>");
      }
    } catch (Exception e) {
      e.printStackTrace();
      out.close();
    } finally {
      try {
        if (rs != null) rs.close();
        if (pstmt != null) pstmt.close();
        if (conn != null) conn.close();
      } catch (Exception e) {
        e.printStackTrace();
      }
    }
  }
}