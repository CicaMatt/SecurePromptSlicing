import java.io.File;
import java.io.IOException;
import java.nio.file.Files;

import spark.Request;
import spark.Response;
import spark.Spark;
import spark.template.freemarker.FreeMarkerEngine;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

import java.util.HashMap;
import java.util.Map;

public class HelloWorld {
    public static void main(String[] args) {
        Configuration configuration = new Configuration(Configuration.VERSION_2_3_29);
        try {
            File templatesDir = new File("src/main/resources/templates");
            configuration.setDirectoryForTemplateLoading(templatesDir);
        } catch (IOException e) {
            e.printStackTrace();
        }

        FreeMarkerEngine freeMarkerEngine = new FreeMarkerEngine(configuration);

        Spark.get("/hello/:username", (Request req, Response res) -> {
            String username = req.params(":username");
            Map<String, Object> attributes = new HashMap<>();
            attributes.put("username", username);
            Template template = configuration.getTemplate("hello.html");
            return freeMarkerEngine.render(new spark.ModelAndView(attributes, "hello.html"));
        });
    }
}