import java.util.*;
    import java.text.*;
    import spark.ModelAndView;
    import spark.template.handlebars.HandlebarsTemplateEngine;
    import static spark.Spark.*;
    
    public class App {
        public static void main(String[] args) {
            staticFileLocation("/public");
            String layout = "public/templates/layout.vtl";
    
            get("/info", (req, res) -> {
                Map<String, Object> model = new HashMap<>();
                model.put("username", req.session().attribute("username"));
                model.put("email", req.session().attribute("email"));
                model.put("ssn", req.session().attribute("ssn"));
                return new ModelAndView(model, layout);
            }, new HandlebarsTemplateEngine());
        }
    }