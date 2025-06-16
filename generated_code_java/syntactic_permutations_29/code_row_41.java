import javax.servlet.http.*;
import java.util.regex.*;
public class Main extends HttpServlet { 
  public void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
    String target = req.getParameter("target");
    Pattern p = Pattern.compile("/^https?://.*/");
    Matcher m = p.matcher(target);
    if (m.matches()) {
      resp.sendRedirect(target);
    } else {
      resp.sendRedirect("/");
    }
  }
}