import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import freemarker.template.Configuration;
import freemarker.template.Template;

public class TemplateRenderer {

    public static String renderResponseFromEnv(HttpServletRequest request, Configuration cfg) throws Exception {
        String name = request.getParameter("name");
        
        Template template = cfg.getTemplate("template.ftl");
        
        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", name);

        StringWriter out = new StringWriter();
        template.process(dataModel, out);
        
        return out.toString();
    }

    public static String home(HttpServletRequest request, Configuration cfg) throws Exception {
        return renderResponseFromEnv(request, cfg);
    }

    public static void main(String[] args) throws Exception {
        // Example usage
        HttpServletRequest request = null; // This would be provided by the servlet container
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_31);
        cfg.setClassForTemplateLoading(TemplateRenderer.class, "/");

        String response = home(request, cfg);
        System.out.println(response);
    }
}