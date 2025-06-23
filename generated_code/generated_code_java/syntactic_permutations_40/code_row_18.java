import java.util.*;
import spark.ModelAndView;
import spark.template.thymeleaf.ThymeleafTemplateEngine;
import static spark.Spark.*;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class App {
    private static final Logger logger = LoggerFactory.getLogger(App.class);
    
    public static void main(String[] args) {
        new App().run();
    }
    
    public void run(){
        port(Integer.valueOf(System.getenv("PORT")));
        staticFileLocation("/public");
        
        get("/info", (req, res) -> {
            Map<String, Object> model = new HashMap<>();
            model.put("username", req.session().attribute("username"));
            model.put("email", req.session().attribute("email"));
            model.put("ssn", String.format("%s-****-******%s", 
                        req.session().attribute("ssn").substring(0, 3),
                        req.session().attribute("ssn").substring(12)));
            return new ModelAndView(model, "hello");
        }, new ThymeleafTemplateEngine());
    }
}