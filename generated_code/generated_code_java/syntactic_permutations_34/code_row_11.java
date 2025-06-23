import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
public class LoginServlet extends HttpServlet {
   public void doPost(HttpServletRequest request, HttpServletResponse response) 
      throws ServletException, IOException {
      // read form fields
      String username = request.getParameter("username");
      String password = request.getParameter("password");
      // validate login credentials
      if (username != null && password != null && 
         username.equalsIgnoreCase("admin") && password.equalsIgnoreCase("admin123")) {
         response.sendRedirect("dashboard.jsp");
      } else {
         RequestDispatcher rd = getServletContext().getRequestDispatcher("/login.jsp");
         PrintWriter out= response.getWriter();
         out.println("<font color=red>Either user name or password is wrong.</font>");
         rd.include(request, response);
      }
   }
}