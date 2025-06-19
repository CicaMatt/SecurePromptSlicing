import java.io.*;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.thymeleaf.TemplateEngine;
import org.thymeleaf.context.WebContext;

public class MyController {
    public HttpServletResponse home(HttpServletRequest req, HttpServletResponse resp) throws Exception {
        TemplateEngine engine = new TemplateEngine();
        WebContext context = new WebContext(req, resp);
        String name = req.getParameter("name");
        context.setVariable("name", name);
        return render_response_from_env(engine, context, env);
    }

    public HttpServletResponse render_response_from_env(TemplateEngine engine, WebContext context, Environment env) throws Exception {
        String template = env.getTemplate();
        String renderedTemplate = engine.process(template, context);
        resp.setContentType("text/html");
        PrintWriter out = resp.getWriter();
        out.print(renderedTemplate);
        return resp;
    }
}