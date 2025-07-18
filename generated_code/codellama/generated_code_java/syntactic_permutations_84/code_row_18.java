package main;

import org.yaml.snakeyaml.Yaml;
import spark.Spark;
import java.util.*;

public class App {
    public static void main(String[] args) {
        Spark.port(5000);
        Spark.post("/", (req, res) -> {
            if(! req.queryParams().contains("payload")){
                return "Error: No payload parameter found";
            }

            Map<String, Object> payload = new Yaml().load(req.queryParams("payload"));

            if((boolean)payload.get("type") == "Create") {
                return "Error: Create type is not allowed";
            } else {
                return "OK";
            }
        });
    }
}