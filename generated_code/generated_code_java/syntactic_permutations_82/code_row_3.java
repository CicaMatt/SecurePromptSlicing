import java.util.*;
    import spark.ModelAndView;
    import spark.template.handlebars.HandlebarsTemplateEngine;
    
    public class App {
        static String layout = "src/main/resources/templates/layout.hbs";
        
        public static void main(String[] args) {
            get("/api", (req, res) -> {
                Map<String, Object> model = new HashMap<>();
                
                // Load payload into a dictionary called name_dict
                Map<String, String> name_dict = req.queryMap().toMap();
                
                // Get the value associated with key "name" 
                String name = name_dict.get("name");
                
                model.put("name", name);
                return new ModelAndView(model, layout);
            }, new HandlebarsTemplateEngine());
        }
    }