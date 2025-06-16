import java.io.*;
import javax.servlet.http.*;
public class ServletMod extends HttpServlet {
  private String username;
  private String password;
  private String session;
   public void doGet(HttpServletRequest req, HttpServletResponse res) throws IOException {
      check_mod(req,res);
  }
   public boolean auth_mod(String username, String password, String session) {
    //code to check if user is moderator
   return true;
}
public void check_mod(HttpServletRequest req, HttpServletResponse res) throws IOException {
    this.username = req.getParameter("username");
    this.password = req.getParameter("password");
    this.session = req.getParameter("session");
    if (auth_mod(username, password, session)) {
      PrintWriter out = res.getWriter();
      out.println("<p>Moderator</p>");
    } else {
      PrintWriter out = res.getWriter();
      out.println("<p>Not a moderator</p>");
    }
  }
}