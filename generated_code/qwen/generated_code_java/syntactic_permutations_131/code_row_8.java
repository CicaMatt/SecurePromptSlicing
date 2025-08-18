import java.io.StringWriter;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class WebApp {

    public static void main(String[] args) {
        // Example usage
        Configuration env = new Configuration(Configuration.VERSION_2_3_30);
        env.setClassForTemplateLoading(WebApp.class, "/templates");
        
        HttpServletRequest request = null; // In a real scenario, this would be provided by the servlet container
        HttpServletResponse response = null; // In a real scenario, this would be provided by the servlet container
        
        try {
            response.getWriter().println(home(env, request));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String home(Configuration env, HttpServletRequest request) throws Exception {
        return render_response_from_env(env, request);
    }

    public static String render_response_from_env(Configuration env, HttpServletRequest request) throws Exception {
        String name = request.getParameter("name");
        Template template = env.getTemplate("template.ftl");
        StringWriter out = new StringWriter();

        if (name != null && !name.isEmpty()) {
            template.process(java.util.Map.of("name", name), out);
        } else {
            template.process(java.util.Map.of(), out);
        }

        return out.toString();
    }
}