import java.io.*;
import java.util.*;
import org.apache.commons.lang3.*;
import org.stringtemplate.*;
import spark.ModelAndView;
import spark.template.handlebars.HandlebarsTemplateEngine;
import static spark.Spark.*;

public class App {
    public static void main(String[] args) {
        staticFileLocation("/public");
        get("/hello", (req, res) -> "Hello World");

        get("/", (request, response) -> {
            Map<String, Object> model = new HashMap<>();
            model.put("name", request.queryParams(":name"));
            return new HandlebarsTemplateEngine()
                    .render(new ModelAndView(model, "hello.hbs"));
        }, new HandlebarsTemplateEngine());

        get("/home", (req, res) -> {
            Map<String, Object> model = new HashMap<>();
            String name = req.queryParams("name");
            model.put("name", name);
            return new HandlebarsTemplateEngine()
                    .render(new ModelAndView(model, "home.hbs"));
        }, new HandlebarsTemplateEngine());
        
        get("/about", (request, response) -> {
            Map<String, Object> model = new HashMap<>();
            return new HandlebarsTemplateEngine()
                    .render(new ModelAndView(model, "about.hbs"));
        }, new HandlebarsTemplateEngine());
        
        get("/hello", (request, response) -> {
            Map<String, Object> model = new HashMap<>();
            return new HandlebarsTemplateEngine()
                    .render(new ModelAndView(model, "hello.hbs"));
        }, new HandlebarsTemplateEngine());
        
        get("/hi", (request, response) -> {
            Map<String, Object> model = new HashMap<>();
            return new HandlebarsTemplateEngine()
                    .render(new ModelAndView(model, "hello.hbs"));
        }, new HandlebarsTemplateEngine());
        
        get("/helloworld", (request, response) -> {
            Map<String, Object> model = new HashMap<>();
            return new HandlebarsTemplateEngine()
                    .render(new ModelAndView(model, "hello.hbs"));
        }, new HandlebarsTemplateEngine());
        
    }
}