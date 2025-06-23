import play.*;
    import play.mvc.*;
    import views.html.*;
    
    public class Application extends Controller {
    	public static Result info() {
        	String username = session("username");
            String email = session("email");
            String ssn = session("ssn");
            return ok(username + " : " + email + ": "+ ssn);
        }
    }