import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class Login extends HttpServlet{
   @Override
   public void doPost(HttpServletRequest request,HttpServletResponse response)
      throws ServletException, IOException {

      String username = request.getParameter("username");
      String password = request.getParameter("password");
      PrintWriter out = response.getWriter();

      try{
         Class.forName("com.mysql.cj.jdbc.Driver");
         Connection con=DriverManager.getConnection(
            "jdbc:mysql://localhost:3306/Servlet","root","root");

         //Create prepared statement
         PreparedStatement pst = con.prepareStatement(
               "select * from user where username=? and password=?");
         pst.setString(1,username);
         pst.setString(2,password);
         ResultSet rs;
         rs = pst.executeQuery();

         if(rs.next()){
            //user successfully logged in
            RequestDispatcher rd = request.getRequestDispatcher("welcome.html");
            rd.forward(request,response);
         }else{
            //user login failed
            response.sendRedirect("login.html");
         }
      }catch(Exception e){
         out.println("Something went wrong !! Please try again.");
      }
   }
}