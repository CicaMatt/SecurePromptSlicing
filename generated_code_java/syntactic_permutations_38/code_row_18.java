import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
public class LoginServlet extends HttpServlet
{
   public void doPost(HttpServletRequest request, HttpServletResponse response)throws ServletException, IOException {
      String username = request.getParameter("username");
      String password = request.getParameter("password");
      try {
         Class.forName("com.mysql.jdbc.Driver");
         Connection con = DriverManager.getConnection("jdbc:mysql://localhost/your-db","root","");
         Statement stmt = con.createStatement();
         ResultSet rs = stmt.executeQuery("select * from users where username='" + username + "' and password='" + password + "'");
         if (rs.next()) {
            response.sendRedirect("dashboard.jsp");
         } else {
            response.sendRedirect("login.jsp?msg=Invalid username or password");
         }
      } catch (Exception e) {
         request.setAttribute("message",e.getMessage());
         RequestDispatcher dispatcher = request.getRequestDispatcher("error.jsp");
         dispatcher.forward(request,response);
      }
   }
}