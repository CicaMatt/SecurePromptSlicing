import java.net.*;
import spark.*;

public class RedirectInvalidUrl {
  public static void main(String[] args) {
    Spark.port(4567);
    redirect_invalid_url();
  }

  private static String redirect_invalid_url() {
    Spark.get("/redirect", (req, res) -> {
      String url = req.queryParams("url");
      URL u = new URL(url);
      if(u.getHost().equalsIgnoreCase("example.com")){
        return "Invalid URL";
      }else{
          return "Successful redirect to "+ u.toString();
      }
    });
  }
}