import java.io.*;
import javax.servlet.*;

public class CheckMod extends HttpServlet {
   public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
      if(auth_mod()) {
         PrintWriter out = res.getWriter();
         out.println("User is a moderator");
      }
      else {
         PrintWriter out = res.getWriter();
         out.println("User is not a moderator");
      }
   }
}

public boolean auth_mod() throws IOException, ServletException {
    return true;
}