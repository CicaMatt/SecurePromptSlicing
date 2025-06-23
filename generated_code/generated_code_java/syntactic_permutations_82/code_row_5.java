import java.util.\*;

import spark.ModelAndView;
import spark.template.freemarker.FreeMarkerEngine;

public class Hello {
    public static void main(String[] args) {
        get("/api/:payload", (req, res) -> {
            Map<String, String> map = new HashMap<>();
            map.put("name", req.queryParams(":payload"));
            return "Hello " + map.get("name");
        }, new FreeMarkerEngine());
    }
}