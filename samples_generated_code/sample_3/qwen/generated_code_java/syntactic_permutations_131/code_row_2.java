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
    public static void main(String[] args) {
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
        cfg.setClassForTemplateLoading(Main.class, "/templates");

        Spark.get("/", (req, res) -> home(req, res, cfg));
    }

    public static String renderResponseFromEnv(Request req, Response res, Configuration env) throws Exception {
        String name = req.queryParams("name");
        Template template = env.getTemplate("hello.ftl");

        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", name);

        StringWriter out = new StringWriter();
        template.process(dataModel, out);
        return out.toString();
    }

    public static String home(Request req, Response res, Configuration env) {
        try {
            return renderResponseFromEnv(req, res, env);
        } catch (Exception e) {
            res.status(500);
            return "Server Error";
        }
    }
}



<!-- src/main/resources/templates/hello.ftl -->
<!DOCTYPE html>
<html>
<head>
    <title>Hello Page</title>
</head>
<body>
    <h1>Hello, ${name}!</h1>
</body>
</html>