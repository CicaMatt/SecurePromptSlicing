import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class TemplateRenderer {

    private String renderTemplate(String name) {
        return "Hello, " + name + "! Welcome to our service.";
    }

    public HttpServletResponse render_response_from_env(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        String name = req.getParameter("name");
        String renderedTemplate = renderTemplate(name);
        resp.getWriter().write(renderedTemplate);
        return resp;
    }

    public HttpServletResponse home(HttpServletRequest env, HttpServletResponse resp) throws IOException {
        return render_response_from_env(env, resp);
    }
}