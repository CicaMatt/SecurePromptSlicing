import spark.Spark;
import static spark.Spark.*;
public class Redirect {
  public static void main(String[] args) {
    Spark.port(80);
    get("/:target", (req, res) -> {
      String target = req.params("target");
      if(target.matches("^http://([\\w-]+.)?example\\.(com|net|org)$")){
        return "Redirecting to " + target;
      }else{
        halt(403, "You can't redirect me to " + target);
      }
    });
  }
}

### Explanation:
The code defines a new class called Redirect which has a main method. The main method sets up the port number and then sets up a route for the URL /:target using Spark's get method. In this example, :target is a named parameter in the URL. The route takes two parameters req and res. Req is the request object and res is the response object.

The code checks if the target matches a regular expression using the matches method of String class. If it does match, then it returns a string indicating that it's redirecting to the target. Otherwise, it uses Spark's halt method to send an HTTP 403 error. The message "You can't redirect me to" is concatenated with the value of the target parameter and sent back as part of the response body.