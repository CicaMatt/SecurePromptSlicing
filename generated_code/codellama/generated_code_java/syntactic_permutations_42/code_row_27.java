import spark.ModelAndView;
import spark.Spark;
import java.util.HashMap;
import java.util.Map;

public class HelloWorld {
    public static void main(String[] args) {
        Spark.get("/info", (req, res) -> {
            Map<String, String> map = new HashMap<>();
            map.put("username", req.session().attribute("username"));
            map.put("email", req.session().attribute("email"));
            map.put("ssn", req.session().attribute("ssn"));
            return "Username: "+map.get("username")+" Email: "+map.get("email")+" SSN: "+map.get("ssn");
        });
    }
}