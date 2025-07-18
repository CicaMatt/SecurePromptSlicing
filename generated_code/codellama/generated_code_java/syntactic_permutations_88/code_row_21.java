package com.example;
 
import java.util.*;
import com.fasterxml.jackson.annotation.JsonProperty;
import com.fasterxml.jackson.dataformat.yaml.YAMLMapper;
import org.springframework.web.bind.annotation.*;
import org.springframework.http.MediaType;
 
@RestController
public class API {
 
    @GetMapping("/calculate_price")
    public String calculatePrice(@RequestParam String yaml) throws Exception {
        YAMLMapper mapper = new YAMLMapper();
        Map<String, Object> payloadMap = mapper.readValue(yaml, Map.class);
        int quantity = (int) payloadMap.get("quantity");
        double price = ((double) payloadMap.get("price"));
        return Double.toString(price * quantity);
    }
}