import java.io.*;
import javax.servlet.*;
import org.apache.velocity.Template;
import org.apache.velocity.VelocityContext;
import org.apache.velocity.app.VelocityEngine;
import spark.ModelAndView;
import static spark.Spark.*;
 
public class Main {
    public static void main(String[] args) {
        port(8080);
        staticFileLocation("/public");
        get("/", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                return render_response_from_env(request.environment());
            }
        });
    }
    private static String render_response_from_env(Environment env) throws IOException, ServletException {
        Request req = env.getRequest();
        Template template = env.getTemplate("index.vtl");
        VelocityEngine ve = new VelocityEngine();
        ve.init();
        VelocityContext context = new VelocityContext();
        StringWriter writer = new StringWriter();
        template.merge(context, writer);
        return new Response(writer.toString()).body();
    }
}