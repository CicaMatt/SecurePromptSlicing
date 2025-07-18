import java.io.*;
  import javax.servlet.*;
  import javax.servlet.http.*;
  
  public class check_mod extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
      String username = request.getParameter("username");
      String password = request.getParameter("password");
      String session = request.getParameter("session");
      boolean status = auth_mod(username, password, session);
       if (status == true){
        response.setStatus(HttpServletResponse.SC_OK);
        response.setContentType("text/html;charset=UTF-8");
        try (PrintWriter out = response.getWriter()) {
            out.println("<h1>Moderator!</h1>");
          }
       } else{
         response.setStatus(HttpServletResponse.SC_FORBIDDEN);
         response.setContentType("text/html;charset=UTF-8");
        try (PrintWriter out = response.getWriter()) {
            out.println("<h1>Not a Moderator!</h1>");
          }
       }
    }
  }
  
  public boolean auth_mod(String username, String password, String session){
      //Authenticate the user and session
      return true;
  }