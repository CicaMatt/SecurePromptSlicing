import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.*;
import freemarker.template.*;

public class HelloWorld extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
    Configuration cfg = new Configuration();
    cfg.setClassForTemplateLoading(this.getClass(), "/");
    Template template = cfg.getTemplate("hello.html");
    StringWriter writer = new StringWriter();
    template.process(null, writer);
    response.setContentType("text/html");
    response.setCharacterEncoding("UTF-8");
    response.getWriter().println(writer.toString());
  }
}