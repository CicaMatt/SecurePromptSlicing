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
        Spark.get("/", (req, res) -> home(req, res));
    }

    public static String home(Request req, Response res) {
        return renderResponseFromEnv(new Environment(req));
    }

    public static String renderResponseFromEnv(Environment env) {
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
        cfg.setClassForTemplateLoading(Main.class, "/templates");
        try {
            Template template = cfg.getTemplate("template.ftl");
            StringWriter writer = new StringWriter();
            Map<String, Object> dataModel = new HashMap<>();
            dataModel.put("name", env.getNameParameter());
            template.process(dataModel, writer);
            return writer.toString();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    static class Environment {
        private final Request request;

        public Environment(Request request) {
            this.request = request;
        }

        public String getNameParameter() {
            return request.queryParams("name");
        }
    }
}