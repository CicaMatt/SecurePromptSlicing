import java.io.\*;
import javax.servlet.\*;

public class Main extends HttpServlet {
  private static final long serialVersionUID = 1L;
  
  protected void doGet(HttpServletRequest req, HttpServletResponse resp)
      throws ServletException, IOException {
    String name = req.getParameter("name");
    Template template = env.getTemplate("index.ftl");
    String renderedTemplate = FreeMarkerTemplateUtils.processTemplateIntoString(template, name);
    resp.getWriter().write(renderedTemplate);
  }
}