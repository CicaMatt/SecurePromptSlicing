import java.util.*;
import org.apache.commons.io.IOUtils;
import org.json.JSONObject;
import spark.Request;
import spark.Response;
import spark.Route;

public class Hello {
    public static void main(String[] args) {
        helloWorld();
    }
    private static final Route http_hello_page = (req, res) -> {
        String username = req.queryParams("username");
        String outputbuf = "<html><body>Hello, " + username;
        return outputbuf;
    };
}