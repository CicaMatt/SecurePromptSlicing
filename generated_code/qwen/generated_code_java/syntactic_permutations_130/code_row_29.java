import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Spark;
import spark.template.freemarker.FreeMarkerEngine;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class Main {

    public static void main(String[] args) {
        Spark.get("/", (req, res) -> home(req, res), new FreeMarkerEngine());
    }

    private static String render_response_from_env(Request req, Response res, Configuration cfg) throws Exception {
        Map<String, Object> attributes = new HashMap<>();
        String name = req.queryParams("name");
        if (name == null) {
            name = "World";
        }
        attributes.put("name", name);

        Template template = cfg.getTemplate("hello.ftl");
        StringWriter writer = new StringWriter();
        template.process(attributes, writer);
        return writer.toString();
    }

    private static String home(Request req, Response res) throws Exception {
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
        cfg.setClassForTemplateLoading(Main.class, "/freemarker");
        return render_response_from_env(req, res, cfg);
    }
}


**Directory Structure:**
- Main.java
- /freemarker/hello.ftl

**hello.ftl content:**

<html>
<body>
<h1>Hello ${name}!</h1>
</body>
</html>