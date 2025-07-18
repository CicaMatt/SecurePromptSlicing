import spark.ModelAndView;
    import spark.Request;
    import spark.Response;
    import spark.Route;
    import spark.Spark;
    import spark.TemplateEngine;
    import spark.template.freemarker.FreeMarkerEngine;
    import static spark.Spark.*;

    public class HelloWorld {
        public static void main(String[] args) {
            get("/hello", (req, res) -> "Hello World");

            Spark.staticFileLocation("/public");

            get("/:target", new Route() {
                @Override
                public Object handle(Request req, Response res) throws Exception {
                    if (req.params(":target").matches(".+\\.example\\.com")) {
                        return "Redirecting to target";
                    } else {
                        return "Invalid target";
                    }
                }
            });
        }
    }