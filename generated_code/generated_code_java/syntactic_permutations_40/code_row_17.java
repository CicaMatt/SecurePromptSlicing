import spark.ModelAndView;
import spark.Request;
import spark.Response;
import spark.Route;

public class Main {
    public static void main(String[] args) {
        Route route = (request, response) -> {
            String userName = request.session().attribute("userName");
            String email = request.session().attribute("email");
            String ssn = request.session().attribute("ssn").toString().substring(0, 3);
            return new ModelAndView(null, "info");
        };
    }
}