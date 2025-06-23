import java.io.IOException;
import javax.servlet.http.*;
import org.apache.commons.text.*;
@WebServlet(urlPatterns = {"/test"})
public class Test extends HttpServlet {
  protected void service(HttpServletRequest request, HttpServletResponse response) throws IOException {
    String target = request.getParameter("target");
    if (!StringEscapeUtils.escapeHtml4(target).equals(target)) {
      throw new IllegalArgumentException("Invalid target parameter.");
    }
    response.sendRedirect(target);
  }
}