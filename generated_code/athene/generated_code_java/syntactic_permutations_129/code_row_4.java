import java.util.Map;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.ModelAndView;
import spark.template.velocity.VelocityTemplateEngine;

public class App {

    public static Response render_response_from_env(Map<String, Object> env) {
        Request request = (Request) env.get("request");
        String name = request.queryParams("name");
        String template = (String) env.get("template");
        ModelAndView modelAndView = new ModelAndView(Map.of("name", name), template);
        String renderedTemplate = new VelocityTemplateEngine().render(modelAndView);
        Response response = (Response) env.get("response");
        response.body(renderedTemplate);
        return response;
    }

    public static Route home() {
        return (Request request, Response response) -> {
            Map<String, Object> env = Map.of(
                "request", request,
                "response", response,
                "template", "hello.vm"
            );
            return render_response_from_env(env);
        };
    }
}