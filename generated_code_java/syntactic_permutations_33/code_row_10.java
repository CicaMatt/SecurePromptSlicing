import spark.ModelAndView;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.template.velocity.VelocityTemplateEngine;

public class App {
  public static void main(String[] args) {
    Redirect redirect = new Redirect();

    get("/:url", redirect, new Route() {
      @Override
      public Object handle(Request req, Response res) {
        String url = req.params(":url");
        return redirect.redirect_invalid_url(url);
      }
    });
  }
}

class Redirect {
  void redirect_invalid_url(String url) {
    if (url == "example.com") {
      return url;
    } else {
      return "error message";
    }
  }
}