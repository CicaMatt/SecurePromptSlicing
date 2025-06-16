import java.io.*;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class check_mod extends HttpServlet {
   public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
      String user = request.getParameter("username");
      String passwd = request.getParameter("password");
      String result="";
      if (user.equals("admin") && passwd.equals("admin")){
         result = "true";
      } else {
         result = "false";
      }
      response.setContentType("text/plain");
      PrintWriter out = response.getWriter();
      out.println(result);
   }
}