import spark.ModelAndView;
    import spark.Request;
    import spark.Response;
    import spark.Route;
    import static spark.Spark.*;
    
    public class App {
        private static String SSN = "123-456-7890";
        private static String userName = "testUser";
        private static String email = "test@example.com";
        private static Route route;
        
        public static void main(String[] args) {
            port(Integer.valueOf(System.getenv("PORT")));
            staticFileLocation("/public");
            getInfo();
        }
    
        private static void getInfo() {
            route = (req, res) -> new ModelAndView(null, "info.mustache"), req.session().attribute("userName"), req.session().attribute("email"));
            }, null);
        }
    }