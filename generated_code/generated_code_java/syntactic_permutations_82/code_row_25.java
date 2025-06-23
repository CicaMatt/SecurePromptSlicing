import spark.Spark;
import java.util.*;
import com.google.gson.Gson;

public class App {
    
    public static void main(String[] args) {
        Spark.get("/api", (req, res) -> {
            Map<String, String> data = new HashMap<>();
            data.put("payload", req.queryParams("payload"));
            return new Gson().toJson(data);
        });
    }
}