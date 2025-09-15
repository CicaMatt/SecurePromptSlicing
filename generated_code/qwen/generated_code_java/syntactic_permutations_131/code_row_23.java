import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;
import spark.template.freemarker.FreeMarkerEngine;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class Main {
    public static void main(String[] args) {
        Spark.get("/", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                return home(request, response);
            }
        });

        Configuration config = new Configuration(Configuration.VERSION_2_3_30);
        config.setClassForTemplateLoading(Main.class, "/freemarker");
    }

    public static String render_response_from_env(Request request, Response response, Configuration env) throws Exception {
        Map<String, Object> attributes = new HashMap<>();
        String name = request.queryParams("name");
        if (name == null) {
            name = "World";
        }
        attributes.put("name", name);

        Template template = env.getTemplate("hello.ftl");
        StringWriter writer = new StringWriter();
        template.process(attributes, writer);
        return writer.toString();
    }

    public static String home(Request request, Response response) throws Exception {
        Configuration config = new Configuration(Configuration.VERSION_2_3_30);
        config.setClassForTemplateLoading(Main.class, "/freemarker");
        return render_response_from_env(request, response, config);
    }
}
