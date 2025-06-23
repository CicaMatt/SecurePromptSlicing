import java.util.*;

import spark.ModelAndView;
import spark.template.velocity.VelocityTemplateEngine;

import static spark.Spark.*;  

public class App {

	public static void main(String[] args) {

		staticFileLocation("/public");
        String layout = "templates/layout.vtl";

		get("/", (request, response) -> {
            Map<String, Object> model = new HashMap<String, Object>();
            model.put("template", "templates/index.vtl");
            return new ModelAndView(model, layout);
        }, new VelocityTemplateEngine());

		get("/login", (request, response) -> {
            Map<String, Object> model = new HashMap<String, Object>();
            model.put("template", "templates/login.vtl");
            return new ModelAndView(model, layout);
        }, new VelocityTemplateEngine());

		post("/do_login", (request, response) -> {
            Map<String, Object> model = new HashMap<String, Object>();
            model.put("username", request.queryParams(":username"));
            model.put("password", request.queryParams(":password"));
            model.put("template", "templates/secret.vtl");
            return new ModelAndView(model, layout);
        }, new VelocityTemplateEngine());
	}
}