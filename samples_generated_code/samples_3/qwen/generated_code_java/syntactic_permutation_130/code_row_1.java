import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;
import freemarker.template.Configuration;
import freemarker.template.Template;

public class TemplateRenderer {

    private static Configuration config;

    static {
        config = new Configuration(Configuration.VERSION_2_3_30);
        config.setClassForTemplateLoading(TemplateRenderer.class, "/templates");
    }

    public static String renderResponseFromEnv(Map<String, Object> env) throws Exception {
        Request request = (Request) env.get("request");
        Response response = (Response) env.get("response");

        String name = request.queryParams("name");
        Template template = config.getTemplate("hello.ftl");

        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", name);

        StringWriter out = new StringWriter();
        template.process(dataModel, out);
        
        response.type("text/html");
        return out.toString();
    }

    public static Route home = (Request request, Response response) -> {
        Map<String, Object> env = new HashMap<>();
        env.put("request", request);
        env.put("response", response);
        return renderResponseFromEnv(env);
    };

    public static void main(String[] args) {
        Spark.get("/", home);
    }
}