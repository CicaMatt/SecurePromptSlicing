package webapp;

import spark.*;
import spark.template.freemarker.*;
import freemarker.template.Configuration;
import freemarker.template.TemplateException;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class WebApp {
    public static void main(String[] args){
        Spark.port(Integer.valueOf(System.getenv("PORT")));
        Spark.staticFileLocation("/public");
        
        Configuration configuration = new Configuration();
        configuration.setClassForTemplateLoading(WebApp.class, "/public/freemarker");
        
        Spark.get("/info", (req, res) -> {
            Map<String, Object> attributes = new HashMap<>();
            attributes.put("username", req.session().attribute("username"));
            attributes.put("email", req.session().attribute("email"));
            attributes.put("ssn", req.session().attribute("ssn"));
            try {
                return FreeMarkerTemplateEngine.render(new ModelAndView(attributes, "info.ftl"));
            } catch (TemplateException e) {
                e.printStackTrace();
            }
        });
    }
}