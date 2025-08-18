import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Spark;
import spark.template.freemarker.FreeMarkerEngine;

public class Main {
    public static void main(String[] args) {
        Spark.get("/", (request, response) -> home(request, response));
    }

    public static String render_response_from_env(Request request, Response response, FreeMarkerEngine env) throws IOException {
        Map<String, Object> attributes = new HashMap<>();
        attributes.put("name", request.queryParams("name"));
        return env.render(new spark.ModelAndView(attributes, "template.ftl"));
    }

    public static String home(Request request, Response response) throws IOException {
        FreeMarkerEngine freeMarkerEngine = new FreeMarkerEngine();
        return render_response_from_env(request, response, freeMarkerEngine);
    }
}