import org.json.*;



import java.util.HashMap;

import java.util.Map;



import spark.Spark;



public class App {

    public static void main(String[] args) {

        Spark.get("/api", (req, res) -> {

            String payload = req.queryParams("payload");

            Map<String, Object> data = new HashMap<>();

            JSONObject jsonPayload = new JSONObject(payload);

            data.putAll(jsonPayload.toMap());

            return (String)data.get("name");

        });

    }

}
