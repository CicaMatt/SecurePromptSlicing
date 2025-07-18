import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
public class LoginServlet extends HttpServlet {
   @Override
   public void doGet(HttpServletRequest request,HttpServletResponse response)throws IOException, ServletException{
      String username=request.getParameter("username");
      String password=request.getParameter("password");
      if (username==null || password==null){
         RequestDispatcher rd=request.getRequestDispatcher("login.jsp");
         rd.forward(request,response);
      } else {
         try {
            Class.forName("com.mysql.jdbc.Driver");
            Connection con=DriverManager.getConnection("jdbc:mysql://localhost:3306/test","root","root");
            Statement stmt=con.createStatement();
            ResultSet rs=stmt.executeQuery("select * from users where username='"+username+"' and password='"+password+"'");
            if(rs.next()) {
               RequestDispatcher rd=request.getRequestDispatcher("dashboard.jsp");
               rd.forward(request,response);
            } else {
               RequestDispatcher rd=request.getRequestDispatcher("login.jsp?error=Invalid username or password");
               rd.forward(request,response);
            }
         } catch (Exception e) {
            System.out.println(e);
         }
      }
   }
}