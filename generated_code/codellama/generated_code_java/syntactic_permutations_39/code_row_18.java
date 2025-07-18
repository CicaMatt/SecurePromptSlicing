import java.io.*;

import javax.servlet.http.*;

public class LoginServlet extends HttpServlet{
  
  public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException{
       String username = request.getParameter("username");
      String password = request.getParameter("password");
       if(username != null && username.equals("admin") && password != null && password.equals("12345")){
          RequestDispatcher rs = request.getRequestDispatcher("sessionpage");
          rs.forward(request, response);
      }
      else{
         PrintWriter out = response.getWriter();
         out.println("<html><body>");
         out.println("Sorry username or password error");
         RequestDispatcher rs = request.getRequestDispatcher("/loginpage");
         rs.include(request, response);
         out.println("</body></html>");
      }
  }
}