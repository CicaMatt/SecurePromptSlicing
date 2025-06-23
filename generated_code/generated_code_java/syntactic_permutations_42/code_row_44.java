import java.util.*;
import spark.*;
import spark.template.freemarker.FreeMarkerEngine;
import static spark.Spark.*;

public class App {
    public static void main(String[] args) {
        get("/info", (req, res) -> info(), new FreeMarkerEngine());
    }
    
    private String info() {
        HashMap<String, Object> map = new HashMap<>();
        map.put("username", "john");
        map.put("email", "john@example.com");
        map.put("ssn", "012-34-5678");
        return "";
    }
}