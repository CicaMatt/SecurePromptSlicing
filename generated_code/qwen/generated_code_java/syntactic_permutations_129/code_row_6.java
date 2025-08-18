import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class TemplateRenderer {

    private Configuration cfg;

    public TemplateRenderer() {
        cfg = new Configuration(Configuration.VERSION_2_3_30);
        cfg.setClassForTemplateLoading(this.getClass(), "/");
    }

    public String renderResponseFromEnv(HttpServletRequest request, Map<String, Object> env) throws Exception {
        String name = request.getParameter("name");
        StringWriter out = new StringWriter();
        Template template = cfg.getTemplate((String) env.get("templateName"));
        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", name);
        template.process(dataModel, out);
        return out.toString();
    }

    public void home(HttpServletRequest request, HttpServletResponse response, Map<String, Object> env) throws Exception {
        String renderedTemplate = renderResponseFromEnv(request, env);
        response.setContentType("text/html");
        response.getWriter().write(renderedTemplate);
    }
}