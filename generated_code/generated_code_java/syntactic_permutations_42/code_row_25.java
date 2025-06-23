package com.example;

    import java.util.*;
    import spark.ModelAndView;
    import spark.template.handlebars.HandlebarsTemplateEngine;

    public class App {
        public static void main(String[] args) {
            get("/info", (req, res) -> {
                Map<String, Object> model = new HashMap<>();
                String username = req.session().attribute("username");
                String email = req.session().attribute("email");
                String ssn = req.session().attribute("ssn");
                model.put("username", username);
                model.put("email", email);
                model.put("ssn", ssn);
                return new ModelAndView(model, "info.hbs");
            }, new HandlebarsTemplateEngine());
        }
    }