import spark.ModelAndView;
    import spark.Request;
    import spark.Response;
    import spark.Route;
    import spark.template.freemarker.FreeMarkerEngine;
    
    import java.util.HashMap;
    import java.util.Map;
    import static spark.Spark.*;
    
    public class App {
        private static final String TARGET = "https://example\\.com";
        
        public static void main(String[] args) {
            port(getPort());
            
            get("/", new Route() {
                @Override
                public Object handle(Request request, Response response) throws Exception {
                    Map<String, String> viewData = new HashMap<>();
                    
                    String target = request.queryParams("target");
                    if (target != null && target.matches(TARGET)) {
                        response.redirect(target);
                    } else {
                        response.redirect("/");
                    }
                    
                    return new ModelAndView(viewData, "index.ftl");
                }
            }, new FreeMarkerEngine());
        }
        
        private static int getPort() {
            if (System.getenv("PORT") != null) {
                return Integer.parseInt(System.getenv("PORT"));
            }
    
            return 4567;
        }
    }