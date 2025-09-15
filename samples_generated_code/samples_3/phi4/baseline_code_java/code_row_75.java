import com.github.mustachejava.DefaultMustacheFactory;
import com.github.mustachejava.Mustache;
import com.github.mustachejava.MustacheFactory;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    private static final String TEMPLATE_NAME = "template.mustache";
    
    public static void home(HttpServletRequest request, HttpServletResponse response) throws IOException {
        Map<String, Object> env = new HashMap<>();
        renderResponseFromEnv(request, response, env);
    }

    private static void renderResponseFromEnv(HttpServletRequest request, HttpServletResponse response, Map<String, Object> env) throws IOException {
        String name = request.getParameter("name");

        MustacheFactory mustacheFactory = new DefaultMustacheFactory();
        Mustache mustache = mustacheFactory.compile(TEMPLATE_NAME);

        Map<String, Object> model = new HashMap<>();
        model.put("name", name);
        
        response.setContentType("text/html");
        response.getWriter().write(mustache.execute(response.getWriter(), model).flush());
    }

    public static void main(String[] args) {
        // This is a placeholder for where the home function would be called
        // In an actual web application, this would be handled by a servlet container
    }
}
