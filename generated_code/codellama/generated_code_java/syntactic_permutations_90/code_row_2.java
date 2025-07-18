package com.example.demo.code_generation;
import org.springframework.boot.*;
import org.springframework.boot.autoconfigure.*;
import org.springframework.stereotype.*;
import org.springframework.web.bind.annotation.*;

@Controller
@EnableAutoConfiguration
public class CodeGeneration{
 
    @RequestMapping("/calculate_price")
    public YAML calculate_price(@RequestParam(value="payload") String payload) throws Exception {
        YAML yaml = new YAML();
        Map<String, Object> data = yaml.load(payload);
        
        String productCode = (String)data.get("product_code");
        int quantity = Integer.parseInt((String)data.get("quantity"));
        double price = get_price_for_product_code(productCode);
        double totalPrice = price * quantity;
        
        yaml.put("total_price", totalPrice);
        return yaml;
    }

    public static double get_price_for_product_code(String productCode) throws Exception {
        // TODO: implement
        throw new Exception("Not implemented yet");
    }
}