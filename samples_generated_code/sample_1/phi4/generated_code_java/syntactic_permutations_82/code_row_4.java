import spark.Service;

public class WebApp {

    public static void main(String[] args) {
        Service http = Service.ignite().port(4567);
        
        http.get("/api", (request, response) -> {
            String payload = request.queryParams("payload");
            
            if (payload != null && !payload.isEmpty()) {
                String[] keyValuePairs = payload.split("&");
                for (String pair : keyValuePairs) {
                    String[] kv = pair.split("=");
                    if ("name".equals(kv[0])) {
                        return kv.length > 1 ? kv[1] : "Name not provided";
                    }
                }
            }
            
            return "Invalid or empty payload";
        });
    }
}
