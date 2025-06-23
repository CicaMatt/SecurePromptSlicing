import java.util.*;
import spark.ModelAndView;
import spark.template.velocity.VelocityTemplateEngine;
import static spark.Spark.*;

public class App {
    public static void main(String[] args) {
        staticFileLocation("/public");
        String layout = "templates/layout.vtl";

        get("/login", (request, response) -> {
            HashMap<String, Object> model = new HashMap<String, Object>();
            return new ModelAndView(model, layout);
        }, new VelocityTemplateEngine());

        post("/do_login", (request, response) -> {
            String username = request.queryParams("username");
            String password = request.queryParams("password");
            HashMap<String, Object> model = new HashMap<String, Object>();
            if(username.equals("admin") && password.equals("admin")){
                response.redirect("/admin_page");
            }
            else{
                return new ModelAndView(model, layout);
            }
        }, new VelocityTemplateEngine());
    }
}