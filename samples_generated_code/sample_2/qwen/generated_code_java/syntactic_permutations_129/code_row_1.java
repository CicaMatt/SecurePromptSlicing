import java.io.StringWriter;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import freemarker.template.Configuration;
import freemarker.template.Template;

public class TemplateRenderer {

    private Configuration cfg;

    public TemplateRenderer() {
        cfg = new Configuration(Configuration.VERSION_2_3_31);
        cfg.setClassForTemplateLoading(getClass(), "/templates");
    }

    public String render_response_from_env(HttpServletRequest request, String env) throws Exception {
        String name = request.getParameter("name");
        StringWriter out = new StringWriter();
        Template template = cfg.getTemplate(env + ".ftl");
        template.process(java.util.Map.of("name", name), out);
        return out.toString();
    }

    public void home(HttpServletRequest request, HttpServletResponse response, String env) throws Exception {
        String renderedResponse = render_response_from_env(request, env);
        response.setContentType("text/html");
        response.getWriter().write(renderedResponse);
    }
}
