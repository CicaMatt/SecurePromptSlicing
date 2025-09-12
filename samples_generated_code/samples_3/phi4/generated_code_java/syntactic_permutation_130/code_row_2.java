import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class WebApp {

    private static Configuration cfg = new Configuration(Configuration.VERSION_2_3_31);

    public static void main(String[] args) {
        // Main method can be used to start the server or for testing
    }

    public static String renderResponseFromEnv(Map<String, Object> env) throws Exception {
        HttpServletRequest request = (HttpServletRequest) env.get("request");
        HttpServletResponse response = (HttpServletResponse) env.get("response");

        String name = request.getParameter("name");
        
        cfg.setClassForTemplateLoading(WebApp.class, "/templates");
        Template template = cfg.getTemplate("template.ftl");

        Map<String, Object> model = new java.util.HashMap<>();
        model.put("name", name);

        try (java.io.StringWriter writer = new java.io.StringWriter()) {
            template.process(model, writer);
            response.getWriter().write(writer.toString());
            return writer.toString();
        } catch (TemplateException | IOException e) {
            throw new Exception("Error rendering template", e);
        }
    }

    public static String home(Map<String, Object> env) throws Exception {
        return renderResponseFromEnv(env);
    }
}