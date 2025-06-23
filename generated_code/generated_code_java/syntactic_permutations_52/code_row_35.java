import java.util.*;
import spark.*;
import static spark.Spark.*;
public class HelloWorld {
  public static void main(String[] args) {
    get("/", (req, res) -> {
      return "Hello World!";
    });
    post("/login", (req, res) -> {
      String username = req.queryParams("username");
      String password = req.queryParams("password");
      if(check_if_correct(username, password))
      {
        set_session(username);
        return redirect("/secret");
      }
      else{
          res.status(403);
          return "Access denied";
      }
    });
  }
}