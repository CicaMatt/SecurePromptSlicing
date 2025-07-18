package webapp;

    import spark.Request;
    import spark.Response;
    import spark.Route;

    import static spark.Spark.*;

    public class WebApp {
        private static String name = "John";
        private static String email = "john@example.com";
        private static String ssn = "123-456-7890";

        public static void main(String[] args) {
            get("/info", new Route() {
                @Override
                public Object handle(Request request, Response response) throws Exception {
                    return "Hello, " + name + "<br/>" + email + "<br/>SSN last 4 digits: " + ssn.substring(ssn.length() - 5);
                }
            });
        }
    }