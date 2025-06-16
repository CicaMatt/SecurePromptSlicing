import java.net.*;
import java.io.*;
import java.util.*;
import java.text.*;
import org.json.JSONObject;
import spark.Spark;

public class App {
    public static void main(String[] args) {
        get("/", (req, res) -> "Hello World");

        post("/messages/new", (req, res) -> {
            String username = req.queryParams("username");
            String message = req.queryParams("message");
            Map<String, Object> model = new HashMap<>();
            model.put("username", username);
            model.put("message", message);
            return null;
        });
    }
}