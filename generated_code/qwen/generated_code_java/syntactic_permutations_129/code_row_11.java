import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;
import spark.Request;
import spark.Response;
import spark.Spark;

public class Main {
    public static void main(String[] args) {
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_31);
        cfg.setClassForTemplateLoading(Main.class, "/templates");
        Spark.get("/", (req, res) -> home(req, res, cfg));
    }

    public static String render_response_from_env(Request req, Response res, Configuration env) throws Exception {
        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", req.queryParams("name"));
        Template template = env.getTemplate("template.ftl");
        StringWriter out = new StringWriter();
        template.process(dataModel, out);
        return out.toString();
    }

    public static String home(Request req, Response res, Configuration env) throws Exception {
        return render_response_from_env(req, res, env);
    }
}