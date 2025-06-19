import org.json.*;
    import spark.ModelAndView;
    import spark.Request;
    import spark.Response;
    import spark.Route;
    import spark.Spark;
    import spark.template.freemarker.FreeMarkerEngine;

    import java.util.HashMap;
    import java.util.Map;

    public class Main {
        static String getUser(final Request request, final Response response) {
            Map<String, Object> data = new HashMap<>();
            data.put("username", request.session().attribute("user"));
            data.put("email", request.session().attribute("email"));
            data.put("ssn", request.session().attribute("ssn").toString().substring(5));
    
            return new FreeMarkerEngine().render(new ModelAndView(data, "info"));
        }
    
        public static void main(String[] args) {
            Spark.get("/info", new Route() {
                @Override
                public Object handle(Request request, Response response) {
                    return getUser(request, response);
                }
            });
        }
    }