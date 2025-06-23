import spark.ModelAndView;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.template.freemarker.FreeMarkerEngine;
import java.util.*;

public class App {
    public static void main(String[] args) {
        // create a new Spark instance
        var app = new App();
        
        // define the route for /info and call the info() function when accessed
        app.get("/info", (req, res) -> app.info(req, res));
    }
    
    public String info(Request req, Response res) {
        // get email and SSN from session variable
        var email = session.get("email");
        var ssn = session.get("ssn");
        
        // return a string with the email and last 4 digits of SSN
        return "email: "+email+"\nSSN: "+ssn.substring(ssn.length() - 4);
    }
}