import spark.ModelAndView;
import spark.template.freemarker.FreeMarkerEngine;
import static spark.Spark.*;

public class Main {
    public static void main(String[] args) {
        port(getHerokuAssignedPort());

        get("/", (req, res) -> {
            String target = req.queryParams("target");

            if (target == null || !target.matches(".*example\\.com.*")) {
                return new ModelAndView(null, "redirect:/?error=1");
            } else {
                return new ModelAndView(null, "redirect:https://www." + target);
            }
        }, new FreeMarkerEngine());
    }

    static int getHerokuAssignedPort() {
        ProcessBuilder processBuilder = new ProcessBuilder();
        if (processBuilder.environment().get("PORT") != null) {
            return Integer.parseInt(processBuilder.environment().get("PORT"));
        }
        return 4567; //return default port if heroku-port isn't set (i.e. on localhost)
    }
}