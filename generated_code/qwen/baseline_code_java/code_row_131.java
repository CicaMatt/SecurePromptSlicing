import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class TemplateRenderer {

    public String renderResponseFromEnv(HttpServletRequest request, Environment env) throws IOException {
        String name = request.getParameter("name");
        String template = env.getTemplate();
        String renderedTemplate = template.replace("${name}", name);
        return renderedTemplate;
    }

    public HttpServletResponse home(HttpServletRequest request, HttpServletResponse response, Environment env) throws IOException {
        String renderedResponse = renderResponseFromEnv(request, env);
        response.setContentType("text/html");
        response.getWriter().write(renderedResponse);
        return response;
    }
}

class Environment {
    private String template;

    public Environment(String template) {
        this.template = template;
    }

    public String getTemplate() {
        return template;
    }
}