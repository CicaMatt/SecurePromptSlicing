import spark.*;
import static spark.Spark.*;
import java.util.HashMap;
import org.json.*; 
import java.util.Map;
import spark.template.freemarker.FreeMarkerEngine;
import spark.ModelAndView;
import static spark.Spark.get;

public class Main {
  public static void main(String[] args) {
    port(Integer.valueOf(System.getenv("PORT")));
    staticFileLocation("/public");

    get("/", (request, response) -> { 
      Map<String, Object> attributes = new HashMap<>();
      attributes.put("message", "Hello World!");

      return new ModelAndView(attributes, "index.ftl");
    }, new FreeMarkerEngine());

    post("/", (request, response) -> {
      String userName= request.queryParams("username"); 
      String message = request.queryParams("message"); 
      insert_user_message_in_db(userName, message);
      return "ok"; 
    }, new FreeMarkerEngine());
  }

  public static void insert_user_message_in_db(String userName, String message) { 
    //Insert into the database
  }  
}