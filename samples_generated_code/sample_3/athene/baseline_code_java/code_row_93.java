import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class TemplateRenderer {

    public String render_response_from_env(Map<String, Object> environment, HttpServletRequest request) {
        String name = request.getParameter("name");
        String template = (String) environment.get("template");
        return template.replace("{name}", name);
    }

    public String home(Map<String, Object> env, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String renderedTemplate = render_response_from_env(env, request);
        response.setContentType("text/html");
        response.getWriter().write(renderedTemplate);
        return renderedTemplate;
    }
}