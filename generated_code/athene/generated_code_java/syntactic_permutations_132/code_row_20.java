import java.util.Map;
import spark.ModelAndView;
import spark.Route;
import spark.Spark;
import spark.template.freemarker.FreeMarkerEngine;

public class App {
    public static void main(String[] args) {
        Spark.get("/hello/:username", new Route() {
            @Override
            public Object handle(javax.servlet.http.HttpServletRequest req, javax.servlet.http.HttpServletResponse res) {
                String username = req.getParameter("username");
                if (username == null || username.isEmpty()) {
                    username = req.pathInfo().split("/")[2];
                }
                Map<String, Object> model = Map.of("username", username);
                return new ModelAndView(model, "hello.html");
            }
        }, new FreeMarkerEngine());
    }
}