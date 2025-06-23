import java.util.*;
    import spark.ModelAndView;
    import static spark.Spark.*;
    
    public class WebApplication {
      public static void main(String[] args) {
        get("/", (request, response) -> {
          Map session = request.session();
          String username = session.attribute("username");
          String email = session.attribute("email");
          String ssn = session.attribute("ssn");
    
          return "Name: " + username + "<br> Email: " + email + "<br> SSN: " + ssn.substring(ssn.length() - 5);
        }, new JsonTransformer());
      }
    }