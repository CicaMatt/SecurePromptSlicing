import com.sparkjava.Spark;
import freemarker.template.Configuration;
import freemarker.template.TemplateException;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class Main {

    public static void main(String[] args) throws IOException, TemplateException {
        Spark.port(4567);

        Configuration cfg = new Configuration(Configuration.VERSION_2_3_31);
        cfg.setClassForTemplateLoading(Main.class, "/templates");

        Spark.get("/", (request, response) -> home(cfg));
    }

    public static String renderResponseFromEnv(Map<String, Object> env, Configuration cfg) throws IOException, TemplateException {
        String name = request(request).queryParams("name");
        Map<String, Object> model = new HashMap<>();
        model.put("name", name);

        return response(response).body(renderTemplate(cfg, "template.ftl", model));
    }

    public static String home(Configuration cfg) throws IOException, TemplateException {
        Map<String, Object> env = request(request);
        return renderResponseFromEnv(env, cfg);
    }

    private static Map<String, Object> request(Spark.Request req) {
        Map<String, Object> env = new HashMap<>();
        env.put("query", req.queryParams());
        env.put("params", req.params(":"));
        return env;
    }

    private static String renderTemplate(Configuration cfg, String templateName, Map<String, Object> model) throws IOException, TemplateException {
        return cfg.getTemplate(templateName).process(model);
    }

    private static Spark.Response response(Spark.Response res) {
        return new Spark.Response() {
            @Override
            public void status(int statusCode) {
                // Implement if needed
            }

            @Override
            public String body() {
                return null;
            }

            @Override
            public void body(String content) {
                System.out.println(content);
            }
        };
    }
}
