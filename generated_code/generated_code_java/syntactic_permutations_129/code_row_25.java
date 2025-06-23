import java.util.*;
import spark.*;
public class Solution {
    public static void main(String[] args) {
        Spark.get("/home", (req, res)->render_response_from_env(env));
    }
    private static String render_response_from_env(Environment env) {
        Map<String, String> map = new HashMap<>();
        map.put("name", req.queryParams(":name"));
        return env.render(map);
    }
}