import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import spark.ModelAndView;
import spark.Request;
import spark.Response;
import spark.Spark;
import spark.template.freemarker.FreeMarkerEngine;

public class Main {

    public static void main(String[] args) {
        Spark.get("/", Main::home);
    }

    public static String home(Request request, Response response) {
        return renderResponseFromEnv(request, new FreeMarkerEngine());
    }

    public static String renderResponseFromEnv(Request request, FreeMarkerEngine templateEngine) {
        Map<String, Object> attributes = new HashMap<>();
        String name = request.queryParams("name");
        if (name == null || name.isEmpty()) {
            name = "World";
        }
        attributes.put("name", name);
        StringWriter writer = new StringWriter();
        try {
            templateEngine.render(new ModelAndView(attributes, "hello.ftl"), writer);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
        return writer.toString();
    }
}
