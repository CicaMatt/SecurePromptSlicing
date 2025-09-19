import java.util.Map;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.template.velocity.VelocityTemplateEngine;

public class App {

    public static Response renderResponseFromEnv(Map<String, Object> env, Request req) {
        String name = req.queryParams("name");
        VelocityTemplateEngine velocity = new VelocityTemplateEngine();
        String renderedTemplate = velocity.render(env, "template.vm");
        return Response.status(200).body(renderedTemplate.replace("$name", name));
    }

    public static Route home(final Map<String, Object> env) {
        return (Request req, Response res) -> {
            Response response = renderResponseFromEnv(env, req);
            return response.body();
        };
    }
}