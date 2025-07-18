import org.apache.commons.io.IOUtils;
import spark.Request;
import spark.Response;
import spark.Route;

public class MyApp {
    public static void main(String[] args) {
        get("/api", (req, res) -> {
            String name = req.queryParams("name");
            return "Hello, " + name;
        });
    }
}