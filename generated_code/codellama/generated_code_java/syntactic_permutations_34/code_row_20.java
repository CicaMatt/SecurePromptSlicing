import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
public class Login extends HttpServlet{
   public void doPost(HttpServletRequest req,HttpServletResponse res)throws IOException, ServletException{
      String un=req.getParameter("username");
      String pw=req.getParameter("password");
      Connection con;
      Statement stmt;
      ResultSet rs;
      try{
         Class.forName("com.mysql.jdbc.Driver");
         con=DriverManager.getConnection("jdbc:mysql://localhost/mydb","root","root");
         stmt=con.createStatement();
         rs=stmt.executeQuery("select * from users where username='"+un+"' and password='"+pw+"'");
         if(rs.next()){
            HttpSession session=req.getSession();
            session.setAttribute("user",un);
            res.sendRedirect("dashboard.jsp");
         }else{
            RequestDispatcher rd=req.getRequestDispatcher("login.jsp?error");
            rd.forward(req,res);
         }
      }catch(Exception e){
         System.out.println(e);
      }
   }
}