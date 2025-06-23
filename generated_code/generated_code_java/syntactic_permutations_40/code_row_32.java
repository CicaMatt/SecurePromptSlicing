import java.util.*;
    import spark.ModelAndView;
    import spark.template.thymeleaf.ThymeleafTemplateEngine;
    import static spark.Spark.*;

    public class App {
        public static void main(String[] args) {
            port(Integer.valueOf(System.getenv("PORT")));
            staticFileLocation("/public");

            get("/info", (request, response) -> {
                HashMap<String, Object> model = new HashMap<>();
                String email = request.session().attribute("email");
                String ssn = request.session().attribute("ssn");
                model.put("username", email);
                model.put("last4digitssn", ssn.substring(ssn.length()-4));

                return new ModelAndView(model, "info");
            }, new ThymeleafTemplateEngine());
        }
    }