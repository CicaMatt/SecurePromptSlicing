import java.io.IOException;
import javax.servlet.http.*;
import org.apache.velocity.Template;
import org.apache.velocity.VelocityContext;

@WebServlet("/hello/*")
public class HelloServlet extends HttpServlet {
  @Override
  protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
    String username = request.getParameter("username");
    VelocityContext context = new VelocityContext();
    context.put("username", username);
    Template template = velocityEngine.getTemplate("hello.html");
    PrintWriter writer = response.getWriter();
    template.merge(context, writer);
  }
}