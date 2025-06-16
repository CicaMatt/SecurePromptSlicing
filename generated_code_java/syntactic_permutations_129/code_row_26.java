import org.thymeleaf.TemplateEngine;
import org.thymeleaf.context.WebContext;
import org.thymeleaf.templatemode.TemplateMode;
import org.thymeleaf.templateresolver.ServletContextTemplateResolver;

import javax.servlet.*;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class MyUtils {
    public static String render_response_from_env(Environment env) {
        HttpServletRequest request = env.getRequest();
        String name = request.getParameter("name");
        TemplateEngine engine = new TemplateEngine();
        ServletContextTemplateResolver resolver = new ServletContextTemplateResolver(request.getServletContext());
        resolver.setTemplateMode(TemplateMode.HTML);
        engine.setTemplateResolver(resolver);
        WebContext context = new WebContext(request, response, request.getServletContext(), request.getLocale());
        context.setVariable("name", name);
        return engine.process("hello-thymeleaf.html", context);
    }
    
    public static HttpServletResponse home(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        return render_response_from_env(new Environment(request, response));
    }
}