import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class HelloWorld extends HttpServlet {
  public void doGet(HttpServletRequest req, HttpServletResponse res)
      throws ServletException, IOException {
    String url = "jdbc:mysql://localhost/example";
    Connection con = null;
    try{
        Class.forName("com.mysql.cj.jdbc.Driver");
        con=DriverManager.getConnection(url,"username","password");
        Statement stmt=con.createStatement();  
        ResultSet rs=stmt.executeQuery("SELECT * FROM users WHERE user_id='moderator'");  
        while(rs.next()){
            String name=rs.getString("name");
            System.out.println("Name: "+name);
        }
    } catch (Exception e) {
      res.getWriter().print(e.getMessage());
  } finally {
    if (con != null) {
      try {
          con.close();
      } catch (SQLException ex) {
        res.getWriter().print(ex.getMessage());
      }
    }
  }
}