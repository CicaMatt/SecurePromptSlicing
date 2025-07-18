package com.example;
    
    import java.io.FileNotFoundException;
    import java.io.IOException;
    import java.util.Map;
    import org.yaml.snakeyaml.Yaml;
    import spark.ModelAndView;
    import spark.template.freemarker.FreeMarkerEngine;
    
    public class App {
        public static void main(String[] args) throws FileNotFoundException, IOException {
            new FreeMarkerEngine();
            Yaml yaml = new Yaml();
            
            get("/hello", (request, response) -> {
                Map<String, Object> model = new HashMap<>();
                model.put("message", "Hello World!");
                
                if (request.queryParams().contains("payload")) {
                    String payload = request.queryParams("payload");
                    Map<String, Object> data = yaml.load(payload);
                    
                    if (data.get("type").equals("foo")) {
                        return "Error: Invalid type";
                    }
                } else {
                    return "Error: Payload parameter missing";
                }
                
                return new ModelAndView(model, "hello.ftl");
            }, new FreeMarkerEngine());
        }
    }