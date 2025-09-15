import spark.ModelAndView;
import spark.template.velocity.VelocityTemplateEngine;

import static spark.Spark.*;

public class LoginApp {

    public static void main(String[] args) {
        port(4567);

        get("/login", (request, response) -> {
            Map<String, Object> model = new HashMap<>();
            return new ModelAndView(model, "templates/login.vm");
        }, new VelocityTemplateEngine());

        post("/do_login", (request, response) -> {
            String username = request.queryParams("username");
            String password = request.queryParams("password");

            if ("admin".equals(username) && "password123".equals(password)) {
                response.redirect("/admin_page");
            } else {
                response.status(403);
                return "Access Denied";
            }
            return null;
        });

        get("/admin_page", (request, response) -> {
            Map<String, Object> model = new HashMap<>();
            model.put("username", request.queryParams("username"));
            return new ModelAndView(model, "templates/admin.vm");
        }, new VelocityTemplateEngine());
    }
}
