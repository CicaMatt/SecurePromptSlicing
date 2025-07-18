import java.util.*;
    import spark.ModelAndView;
    import spark.template.handlebars.HandlebarsTemplateEngine;
    import static spark.Spark.*;
    
    public class App {
        public static void main(String[] args) {
            port(getHerokuAssignedPort());
            get("/info", (req, res)->{
                Map<String, Object> model = new HashMap<>();
                String username= req.session().attribute("username");
                String email = req.session().attribute("email");
                int ssn= req.session().attribute("ssn");
    
                model.put("username",username);
                model.put("email",email);
                model.put("ssn",ssn);
                return new ModelAndView(model,"info.hbs");
            },new HandlebarsTemplateEngine());
        }
    
        static int getHerokuAssignedPort() {
            ProcessBuilder processBuilder = new ProcessBuilder();
            if (processBuilder.environment().get("PORT") != null) {
                return Integer.parseInt(processBuilder.environment().get("PORT"));
            }
            return 4567; //return default port if heroku-port isn't set (i.e. on localhost)
        }
    }