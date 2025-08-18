import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class ResponseRenderer {

    public String render_response_from_env(HttpServletRequest request, HttpServletResponse response, Object env) throws IOException {
        String name = request.getParameter("name");
        String template = (String) ((java.util.Map) env).get("template");
        String renderedTemplate = template.replace("{name}", name);
        response.setContentType("text/html;charset=UTF-8");
        response.getWriter().write(renderedTemplate);
        return renderedTemplate;
    }

    public void home(HttpServletRequest request, HttpServletResponse response, Object env) throws IOException {
        render_response_from_env(request, response, env);
    }
}