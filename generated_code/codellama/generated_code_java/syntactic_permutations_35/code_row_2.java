import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
public class Login extends HttpServlet {
  public void doPost(HttpServletRequest request,HttpServletResponse response)throws ServletException, IOException {
    String username = request.getParameter("username");
    String password = request.getParameter("password");
    try{
      Class.forName("com.mysql.jdbc.Driver");
      Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/login","root","root");
      PreparedStatement ps = con.prepareStatement("select * from users where username=? and password=?");
      ps.setString(1,username);
      ps.setString(2,password);
      ResultSet rs = ps.executeQuery();
      if(rs.next()){
        RequestDispatcher rd = request.getRequestDispatcher("home.html");
        rd.forward(request,response);
      } else{
        RequestDispatcher rd = request.getRequestDispatcher("login.html");
        rd.include(request,response);
      }
    }catch(Exception e){
      System.out.println(e);
    }
  }
}