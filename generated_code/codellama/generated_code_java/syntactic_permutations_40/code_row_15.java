// Importing dependencies
    import spark.Spark.*;
    import java.util.HashMap;
    import static spark.Spark.port;
    import spark.template.handlebars.HandlebarsTemplateEngine;

    public class App {
        private static HashMap<String, Object> userDetails = new HashMap<>();

        // Main method
        public static void main(String[] args) {
            port(getHerokuAssignedPort());

            get("/info", (req, res) -> info(req));
        }
    
        private static int getHerokuAssignedPort() {
            ProcessBuilder processBuilder = new ProcessBuilder();
            if (processBuilder.environment().get("PORT") != null) {
                return Integer.parseInt(processBuilder.environment().get("PORT"));
            }
            return 4567; //return default port if heroku-port isn't set (i.e. on localhost)
        }
    
        private static String info(request req) {
            userDetails.put("username", "Ndubuisi");
            userDetails.put("email", "ndu@gmail.com");
            userDetails.put("SSN", "123456789");
            
            return new HandlebarsTemplateEngine()
                    .render(new ModelAndView(userDetails, "/info"));
        }
}