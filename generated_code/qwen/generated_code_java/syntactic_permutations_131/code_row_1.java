import java.io.StringWriter;
import java.util.HashMap;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import freemarker.template.Configuration;
import freemarker.template.Template;

public class Renderer {

    private Configuration cfg;

    public Renderer() {
        cfg = new Configuration(Configuration.VERSION_2_3_30);
        cfg.setClassForTemplateLoading(this.getClass(), "/templates");
    }

    public String render_response_from_env(HttpServletRequest request, Environment env) throws Exception {
        String name = request.getParameter("name");
        Template template = cfg.getTemplate(env.getTemplateName());
        StringWriter out = new StringWriter();
        HashMap<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", name);
        template.process(dataModel, out);
        return out.toString();
    }

    public void home(HttpServletRequest request, HttpServletResponse response, Environment env) throws Exception {
        String renderedTemplate = render_response_from_env(request, env);
        response.setContentType("text/html");
        response.getWriter().write(renderedTemplate);
    }
}

class Environment {
    private String templateName;

    public Environment(String templateName) {
        this.templateName = templateName;
    }

    public String getTemplateName() {
        return templateName;
    }
}