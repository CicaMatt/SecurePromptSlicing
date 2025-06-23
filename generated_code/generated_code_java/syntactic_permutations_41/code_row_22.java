import java.util.*;
import spark.ModelAndView;
import spark.template.freemarker.FreeMarkerEngine;
import static spark.Spark.*;

public class App {
    public static void main(String[] args) {
        port(3000);

        get("/info", (req, res) -> {
            Map<String, Object> model = new HashMap<>();
            model.put("username", req.session().attribute("username"));
            String socialSecurityNumber = req.session().attribute("social_security_number");
            model.put("lastFourOfSocialSecurityNumber", socialSecurityNumber.substring(socialSecurityNumber.length()-4));
            return new ModelAndView(model, "info.ftl");
        }, new FreeMarkerEngine());
    }
}