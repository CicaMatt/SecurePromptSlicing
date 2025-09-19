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


Make sure to include the Spark framework in your project dependencies:


<dependency>
    <groupId>com.sparkjava</groupId>
    <artifactId>spark-core</artifactId>
    <version>2.9.3</version>
</dependency>


This code sets up a simple web app using Spark Java, creating a route `/api` that processes query parameters from the URL to extract and return the `name` value if present.