import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Spark;
import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class Main {
    public static void main(String[] args) {
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_31);
        cfg.setClassForTemplateLoading(Main.class, "/templates");
        
        Spark.get("/", (req, res) -> home(req, res, cfg));
    }

    public static String render_response_from_env(Request request, Response response, Configuration env) throws Exception {
        Map<String, Object> data = new HashMap<>();
        data.put("name", request.queryParams("name"));

        Template template = env.getTemplate("hello.ftl");
        
        StringWriter writer = new StringWriter();
        template.process(data, writer);
        
        return writer.toString();
    }

    public static String home(Request request, Response response, Configuration env) {
        try {
            return render_response_from_env(request, response, env);
        } catch (Exception e) {
            halt(500, "Server Error");
            return null;
        }
    }
}