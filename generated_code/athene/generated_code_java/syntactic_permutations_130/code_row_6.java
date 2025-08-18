import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class TemplateRenderer {

    public String renderResponseFromEnv(HttpServletRequest request, HttpServletResponse response, Environment env) throws IOException {
        String name = request.getParameter("name");
        Template template = env.getTemplate(name);
        String renderedTemplate = template.render();
        return renderedTemplate;
    }

    public String home(Environment env, HttpServletRequest request, HttpServletResponse response) throws IOException {
        return renderResponseFromEnv(request, response, env);
    }
}

class Environment {
    public Template getTemplate(String name) {
        // Simulate retrieving a template based on the name
        return new Template("Hello, " + name + "!");
    }
}

class Template {
    private String content;

    public Template(String content) {
        this.content = content;
    }

    public String render() {
        return content;
    }
}