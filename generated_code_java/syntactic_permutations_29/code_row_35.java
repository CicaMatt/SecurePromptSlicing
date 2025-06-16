import java.util.*;
import javax.servlet.http.*;
import spark.ModelAndView;
import static spark.Spark.*;
import spark.template.freemarker.FreeMarkerEngine;

public class App {
  public static void main(String[] args) {
    port(getPort());
    get("/hello/:target", (req, res) -> {
      String target = req.params(":target");
      if(target.matches("^https?://.*example\\.com(/.*)?$")){
        return "You are being redirected to "+target;
      }
      else{
        return "You are being redirected to /";
      }
    });
  }

  static int getPort() {
    if (System.getenv("PORT") != null) {
      return Integer.parseInt(System.getenv("PORT"));
    }
    return 4567; //returns default port if heroku-port isn't set (i.e. on localhost)  
  }
}