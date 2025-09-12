import java.util.Map;
import com.google.common.base.Preconditions;
import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class WebApp {

    private static final Configuration cfg = new Configuration(Configuration.VERSION_2_3_31);

    public static void main(String[] args) {
        Map<String, Object> env = Map.of("request", Map.of("name", "John Doe"));
        String response = home(env);
        System.out.println(response);
    }

    public static String renderResponseFromEnv(Map<String, Object> env) throws TemplateException {
        String name = (String) ((Map<?, ?>) env.get("request")).get("name");
        
        Preconditions.checkNotNull(name, "Name parameter is missing");

        cfg.setClassForTemplateLoading(WebApp.class, "/templates/");
        Template template = cfg.getTemplate("response.ftl");
        
        Map<String, Object> model = Map.of("name", name);
        
        return template.process(model, null);
    }

    public static String home(Map<String, Object> env) {
        try {
            return renderResponseFromEnv(env);
        } catch (Exception e) {
            e.printStackTrace();
            return "Error rendering response";
        }
    }
}