import java.util.*;
import javax.servlet.http.*;

public class Moderate extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response)
      throws IOException {
    String username = request.getParameter("username");
    String password = request.getParameter("password");
    String session = request.getParameter("session");

    if (auth_mod(username, password, session)) {
      PrintWriter out = response.getWriter();
      out.print("You are a moderator!");
    } else {
      PrintWriter out = response.getWriter();
      out.print("You are not a moderator!");
    }
  }

  public boolean auth_mod(String username, String password, String session) {
    // Check if the user is a moderator
    return true;
  }
}