import java.io.StringWriter;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class WebApp {

    private Configuration cfg;

    public WebApp() throws Exception {
        cfg = new Configuration(Configuration.VERSION_2_3_31);
        cfg.setDirectoryForTemplateLoading(new java.io.File("templates"));
    }

    public void renderResponseFromEnv(HttpServletRequest request, HttpServletResponse response) throws Exception {
        String name = request.getParameter("name");
        
        Template template = cfg.getTemplate("template.ftlh");

        StringWriter writer = new StringWriter();
        template.process(name, writer);

        response.setContentType("text/html");
        response.getWriter().write(writer.toString());
    }

    public void home(HttpServletRequest request, HttpServletResponse response) throws Exception {
        renderResponseFromEnv(request, response);
    }
}