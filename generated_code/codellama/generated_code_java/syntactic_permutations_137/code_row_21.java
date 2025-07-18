import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class check_mod extends HttpServlet{
  public void doGet(HttpServletRequest request, HttpServletResponse response)throws IOException, ServletException {
   String username=request.getParameter("username");
   String password=request.getParameter("password");
   String session=request.getParameter("session");
    boolean auth_mod=auth_mod(username, password, session);
    if (auth_mod==true) {
      response.getWriter().println("You are a moderator.");
    }
    else{
      response.getWriter().println("You are not a moderator.");
    }
  }
}