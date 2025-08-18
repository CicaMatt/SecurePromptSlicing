import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import org.thymeleaf.TemplateEngine;
import org.thymeleaf.context.Context;
import org.thymeleaf.templateresolver.ClassLoaderTemplateResolver;

public class WebApplication {

    private static final TemplateEngine templateEngine = new TemplateEngine();

    static {
        ClassLoaderTemplateResolver resolver = new ClassLoaderTemplateResolver();
        resolver.setPrefix("/templates/");
        resolver.setSuffix(".html");
        resolver.setCharacterEncoding("UTF-8");
        resolver.setTemplateMode("HTML");
        templateEngine.setTemplateResolver(resolver);
    }

    public String renderResponseFromEnv(HttpServletRequest request) {
        Map<String, Object> env = System.getenv();
        String name = request.getParameter("name");
        
        if (name == null || name.isEmpty()) {
            name = "World";
        }
        
        Context context = new Context();
        context.setVariable("name", name);
        
        return templateEngine.process(env.toString(), context);
    }

    public String home(HttpServletRequest request) {
        return renderResponseFromEnv(request);
    }
}