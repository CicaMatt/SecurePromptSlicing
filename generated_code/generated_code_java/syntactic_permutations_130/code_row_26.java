import java.io.IOException;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.thymeleaf.TemplateEngine;
import org.thymeleaf.context.WebContext;
import org.thymeleaf.templatemode.StandardTemplateModeHandlers;
import org.thymeleaf.templateresolver.ServletContextTemplateResolver;
import org.thymeleaf.templateresolver.StringTemplateResolver;
public class Main {
    public static String render_response_from_env(Environment env) throws IOException, ServletException{
        HttpServletRequest request = (HttpServletRequest) env.get("request");
        String name = request.getParameter("name");
        TemplateEngine engine = new TemplateEngine();
        engine.setTemplateResolver(new ServletContextTemplateResolver());
        engine.setTemplateModeHandlers(StandardTemplateModeHandlers.ALL_TEMPLATE_MODE_HANDLERS);
        WebContext context = new WebContext(request, env.getResponse(), request.getServletContext());
        engine.process("template", context);
        return name;
    }
    public static String home(Environment env) throws IOException, ServletException{
        Response response = render_response_from_env(env);
        return response.body();
    }
}