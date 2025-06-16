import play.mvc.Controller;
    import play.mvc.Result;

    public class Application extends Controller {
        private static final String DOMAIN = "example.com";
    
        public static Result index() {
            String target = request().getQueryString("target");
            if (isValidTarget(target)) {
                return redirect(target);
            } else {
                return badRequest();
            }
        }
    
        private static boolean isValidTarget(String target) {
            final String regex = "^.*" + DOMAIN + ".*$";
            return target.matches(regex);
        }
    }