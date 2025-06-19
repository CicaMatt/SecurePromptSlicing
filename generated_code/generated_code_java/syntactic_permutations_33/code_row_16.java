import java.io.*;
import java.util.HashMap;
import java.util.Map;
import spark.*;

public class Application {
    public static void main(String[] args) {
        Spark.port(9080);
        Spark.get("/url_redirect", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                String url = request.queryParams("url");
                try {
                    redirect_invalid_url(url);
                } catch (Exception e) {
                    return "Invalid URL";
                }
                return "Successfully redirected to: " + url;
            }
        });
    }
}