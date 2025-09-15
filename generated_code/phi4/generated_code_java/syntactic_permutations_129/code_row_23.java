import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

@WebServlet("/renderResponse")
public class RenderResponseServlet extends HttpServlet {

    private Configuration cfg;

    public void init() throws ServletException {
        try {
            cfg = new Configuration(Configuration.VERSION_2_3_31);
            cfg.setClassForTemplateLoading(RenderResponseServlet.class, "/templates");
        } catch (IOException e) {
            throw new ServletException("Cannot load FreeMarker configuration.", e);
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        String name = request.getParameter("name");

        Template template;
        try {
            template = cfg.getTemplate("template.ftl");
            template.process(createDataModel(name), response.getWriter());
        } catch (TemplateException e) {
            throw new ServletException(e);
        }
    }

    private Object createDataModel(String name) {
        return java.util.Collections.singletonMap("name", name);
    }

    public void destroy() {
        // Cleanup code if needed
    }
}
