import spark.ModelAndView;
    import spark.Request;
    import spark.Response;
    import spark.Route;
    import spark.template.freemarker.FreeMarkerEngine;
    
    import static spark.Spark.*;
    
    public class App {
        // Default port is 80 and can be overwritten by heroku or any other provider
        public static final int PORT = Integer.valueOf(System.getenv("PORT"));
        public static void main(String[] args) {
            staticFileLocation("/public");
    
            get("/", new Route() {
                @Override
                public Object handle(Request request, Response response) throws Exception {
                    return "Hello World!";
                }
            });
            
            get("/:target", new Route() {
                @Override
                public Object handle(Request request, Response response) throws Exception {
                    String target = request.params(":target");
                    if (target.matches(".+example.com")) {
                        return "Redirecting to " + target;
                    } else {
                        response.redirect("/");
                    }
                }
            });
        }
    }