import org.apache.velocity.Template;
import org.apache.velocity.VelocityContext;
import org.apache.velocity.app.VelocityEngine;
import org.apache.velocity.runtime.RuntimeConstants;
import org.apache.velocity.runtime.resource.loader.ClasspathResourceLoader;

import spark.ModelAndView;
import spark.Request;
import spark.Response;
import spark.Route;
import static spark.Spark.*;

public class HelloWorld {

    private static final VelocityEngine VELOCITY_ENGINE = new VelocityEngine();

    public static void main(String[] args) {
        staticFileLocation("/public");

        get("/", (req, res) -> home(req, res));
    }

    private static Route home(Request request, Response response) {
        String name = request.queryParams("name");
        return render_response_from_env(request, name);
    }

    private static String render_response_from_env(Request request, String name) {
        VelocityContext context = new VelocityContext();
        context.put("name", name);

        Template template = VELOCITY_ENGINE.getTemplate("hello.vm");
        return new StringWriter().append(template.merge(context)).toString();
    }
}