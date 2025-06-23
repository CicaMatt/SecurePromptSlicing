import java.util.*;

import spark.ModelAndView;
import static spark.Spark.*;

public class User {
  private String username, email, ssn;

  public User(String name, String email, String ssn) {
    this.username = name;
    this.email = email;
    this.ssn = ssn;
  }

  public String getName() {
    return username;
  }

  public String getEmail() {
    return email;
  }

  public String getSsn() {
    return ssn;
  }
}

import java.util.*;

public class UserController {
  private static Map<String, Object> model = new HashMap<>();
  public void info(Request req, Response resp) {
    model.put("user", getUser());
    resp.status(200);
    return "Hello, " + model.get("user") + "!";
  }
  
  private User getUser() {
    String name = session.attribute("name");
    String email = session.attribute("email");
    String ssn = session.attribute("ssn");
    return new User(name, email, ssn);
  }
}

import static spark.Spark.*;

public class Main {
  public static void main(String[] args) {
    port(80);
    
    // Redirect any requests to /hello to /api/hello
    redirect.get("/", "/info");
    
    get("/info", "application/json", (req, res) -> {
      return new UserController().info(req, res);
    });
  }
}