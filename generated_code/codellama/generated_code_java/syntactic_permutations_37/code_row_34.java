import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class Login extends HttpServlet {

  public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
   String username = request.getParameter("username");
    String password = request.getParameter("password");
    String url = "";
   if (username != null && password != null) {
      try {
         // Use the username and password to authenticate against a database
         boolean validUserPass = false;
         if (!validUserPass) {
            url = "/cant_login";
         } else {
            url = "/success";
         }
      } catch (Exception e) {
         System.out.println(e);
          url = "/error";
       }
    } else {
        url = "/invalid_params";
    }
     RequestDispatcher dispatcher = getServletContext().getRequestDispatcher(url);
     dispatcher.forward(request, response);
  }
}