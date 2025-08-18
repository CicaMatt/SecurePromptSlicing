import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import org.apache.velocity.Template;
import org.apache.velocity.VelocityContext;
import org.apache.velocity.app.VelocityEngine;

public class TemplateRenderer {

    public static HttpServletResponse render_response_from_env(VelocityEngine env, HttpServletRequest request, HttpServletResponse response) throws IOException {
        String name = request.getParameter("name");
        Template template = env.getTemplate("template.vm");
        VelocityContext context = new VelocityContext();
        context.put("name", name);
        response.setContentType("text/html");
        template.merge(context, response.getWriter());
        return response;
    }

    public static HttpServletResponse home(VelocityEngine env, HttpServletRequest request, HttpServletResponse response) throws IOException {
        return render_response_from_env(env, request, response);
    }
}