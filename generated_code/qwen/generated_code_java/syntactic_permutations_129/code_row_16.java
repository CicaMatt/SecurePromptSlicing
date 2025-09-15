import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;
import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class Main {

    private static Configuration cfg;

    public static void main(String[] args) {
        Spark.get("/", (Request req, Response res) -> home(req, res));
        
        try {
            cfg = new Configuration(Configuration.VERSION_2_3_30);
            cfg.setClassForTemplateLoading(Main.class, "/templates");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static String render_response_from_env(Request req, Response res) throws Exception {
        Map<String, Object> attributes = new HashMap<>();
        attributes.put("name", req.queryParams("name"));

        Template template = cfg.getTemplate("template.ftl");
        StringWriter writer = new StringWriter();
        template.process(attributes, writer);
        return writer.toString();
    }

    private static String home(Request req, Response res) {
        try {
            return render_response_from_env(req, res);
        } catch (Exception e) {
            e.printStackTrace();
            return "Error processing request";
        }
    }
}
