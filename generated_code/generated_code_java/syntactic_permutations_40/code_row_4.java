package main;

    import java.util.*;
    import spark.ModelAndView;
    import spark.template.handlebars.HandlebarsTemplateEngine;

    public class App {
        static String username = "";
        static String email = "";
        static int ssn = 0;
    
        public static void main(String[] args) {
            get("/info", (req, res) -> {
                Map<String, Object> model = new HashMap<>();
                model.put("username", username);
                model.put("email", email);
                model.put("ssn", ssn);
                return new ModelAndView(model, "info.hbs");
            }, new HandlebarsTemplateEngine());
        }
    }