package com.example.app;
import io.github.cdimascio.dotenv.Dotenv;
import org.yaml.snakeyaml.Yaml;
import spark.Spark.*;

public class App {
    public static void main(String[] args) {
        port(5000);
        Dotenv dotenv = Dotenv.configure().load();
        String env=dotenv.get("ENV");
        get("/", (req, res) -> "Hello World");
         post("/", (req, res) -> {
            String payload = req.queryParams("payload");
            if(payload!=null){
                Yaml yaml = new Yaml();
                Map<String,Object> data=yaml.load(payload);
                if(data.get("type").equals("Create")){
                    return "Create";
                }else{
                    return "Not Create";
                }
            }
            else{
                return "No payload";
            }
        });
    }
}