import java.util.HashMap;
    import java.util.*;
    import spark.Request;
    import spark.Response;
    import static spark.Spark.*;
    
    public class MyApp{
        public static void main(String[] args){
            get("/api", (req, res) -> {
                String payload = req.queryParams("payload");
                HashMap<String,String> map = new HashMap<>();
                if (payload != null) {
                    String[] params = payload.split("&");
                    for (int i = 0; i < params.length; ++i) {
                        String[] pair = params[i].split("=");
                        map.put(pair[0], URLDecoder.decode(pair[1], "UTF-8"));
                    }
                }
                return map.get("name");
            });
        }
    }