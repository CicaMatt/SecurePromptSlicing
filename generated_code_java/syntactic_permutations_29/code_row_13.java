import spark.ModelAndView;
import spark.template.freemarker.FreeMarkerEngine;
import static spark.Spark.*;

public class HelloWorldFreemarkerStyle {
  public static void main(String[] args) {
    port(Integer.valueOf(System.getenv("PORT")));
    staticFileLocation("/public");
    String regex = "https?://([\\w-]+\\.)+example\\.com(/[\\w- ./?%&=]*)?";
    get("/hello", (req, res) -> {
      return new ModelAndView(null, "HelloWorld.ftl");
    }, new FreeMarkerEngine());
  }
}