import org.apache.commons.lang3.StringUtils;
import spark.ModelAndView;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.template.velocity.VelocityTemplateEngine;
import java.util.HashMap;
import java.util.Map;

public class RedirectApp {
    public static final String MATCH_PATTERN = ".*example\\.com";

    /**
     * Method to redirect to the matched target URL
     */
    public static Route handleMatchedTargetUrl = (Request request, Response response) -> {
        Map<String, Object> model = new HashMap<>();
        String target = request.queryParams("target");
        if (!StringUtils.isBlank(target)) {
            model.put("target", target);
            return new ModelAndView(model, "matched-url.vtl");
        } else {
            response.redirect("/");
            return null;
        }
    };
    
    /**
     * Method to redirect to the unmatched target URL
     */
    public static Route handleUnMatchedTargetUrl = (Request request, Response response) -> {
        Map<String, Object> model = new HashMap<>();
        String target = request.queryParams("target");
        if (!StringUtils.isBlank(target)) {
            model.put("target", target);
            return new ModelAndView(model, "unmatched-url.vtl");
        } else {
            response.redirect("/");
            return null;
        }
    };
    
    /**
     * Method to check if the target URL matches a regular expression
     */
    public static Route handleTargetUrl = (Request request, Response response) -> {
        Map<String, Object> model = new HashMap<>();
        String target = request.queryParams("target");
        if (!StringUtils.isBlank(target)) {
            model.put("target", target);
            // Check if the target URL matches a regular expression
            if (target.matches(MATCH_PATTERN)) {
                return new ModelAndView(model, "matched-url.vtl");
            } else {
                return new ModelAndView(model, "unmatched-url.vtl");
            }
        } else {
            response.redirect("/");
            return null;
        }
    };
    
    /**
     * Main method to start the Spark server
     */
    public static void main(String[] args) {
        // Set the port for the Spark server
        int port = 4567;
        // Create a new Spark server
        spark.Spark.port(port);
        // Define the route to handle incoming requests
        spark.Spark.get("/", RedirectApp::handleTargetUrl);
        spark.Spark.get("/matched-url", RedirectApp::handleMatchedTargetUrl);
        spark.Spark.get("/unmatched-url", RedirectApp::handleUnMatchedTargetUrl);
    }
}