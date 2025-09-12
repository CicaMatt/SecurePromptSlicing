import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import org.apache.commons.lang3.StringUtils;

public class ResponseRenderer {

    public static String renderResponseFromEnv(HttpServletRequest request, HttpServletResponse response, Environment env) throws IOException {
        String name = request.getParameter("name");
        Template template = env.getTemplate(name);
        String renderedTemplate = template.render(name);
        response.setContentType("text/html");
        response.getWriter().write(renderedTemplate);
        return renderedTemplate;
    }

    public static void home(HttpServletRequest request, HttpServletResponse response, Environment env) throws IOException {
        String renderedResponse = renderResponseFromEnv(request, response, env);
        // Assuming the response is already written in renderResponseFromEnv
    }
    
    class Environment {
        Template getTemplate(String name) {
            // Dummy implementation for example purposes
            return new Template();
        }
    }
    
    class Template {
        String render(String name) {
            // Dummy implementation for example purposes
            return "Hello, " + name + "!";
        }
    }
}