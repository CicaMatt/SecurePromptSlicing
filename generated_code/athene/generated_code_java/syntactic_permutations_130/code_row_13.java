import java.util.Map;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.template.freemarker.FreeMarkerEngine;

public class App {

    public static Response render_response_from_env(Map<String, Object> env) {
        String name = (String) env.get("name");
        FreeMarkerEngine freeMarkerEngine = new FreeMarkerEngine();
        String templatePath = (String) env.getOrDefault("template", "templates/home.ftl");
        Map<String, Object> attributes = Map.of("name", name);
        String renderedTemplate = freeMarkerEngine.render(new ModelAndView(attributes, templatePath));
        Response response = new Response() {
            @Override
            public void status(int i) {}

            @Override
            public int status() {
                return 200;
            }

            @Override
            public void type(String s) {}

            @Override
            public String type() {
                return "text/html";
            }

            @Override
            public void body(String s) {}

            @Override
            public String body() {
                return renderedTemplate;
            }
        };
        response.body(renderedTemplate);
        response.status(200);
        response.type("text/html");
        return response;
    }

    public static Route home(final Request request, final Response response) {
        Map<String, Object> env = Map.of(
            "name", request.queryParams("name"),
            "template", request.attribute("template")
        );
        return (req, res) -> render_response_from_env(env).body();
    }
}