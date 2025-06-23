import spark.ModelAndView;
import spark.Request;
import spark.Response;
import spark.Route;

import static spark.Spark.*;
public class WebApp {

    public static void main(String[] args) {
        get("/", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                return "Hello World!";
            }
        });
    }
}