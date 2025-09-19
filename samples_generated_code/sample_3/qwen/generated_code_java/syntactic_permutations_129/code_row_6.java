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

public class WebApp {

    private static String render_response_from_env(Configuration cfg, Request request) {
        try {
            String name = request.queryParams("name");
            Template template = cfg.getTemplate("hello.ftl");
            StringWriter writer = new StringWriter();
            Map<String, Object> dataModel = new HashMap<>();
            dataModel.put("name", name != null ? name : "World");
            template.process(dataModel, writer);
            return writer.toString();
        } catch (Exception e) {
            e.printStackTrace();
            return "Error rendering template";
        }
    }

    private static Route home(Configuration cfg) {
        return (Request request, Response response) -> render_response_from_env(cfg, request);
    }

    public static void main(String[] args) {
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
        try {
            cfg.setDirectoryForTemplateLoading(new java.io.File("src/main/resources"));
        } catch (Exception e) {
            e.printStackTrace();
        }

        Spark.get("/", home(cfg));
    }
}