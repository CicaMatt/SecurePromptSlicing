package com.example.calculateprice;
import org.springframework.web.bind.annotation.*;

@RestController
public class CalculatePrice {
    @GetMapping("/calculate_price")
    public String calculatePrice(@RequestParam String yamlPayload) {
        YamlPayload payload = new YamlPayload(yamlPayload);
        float totalPrice = payload.getQuantity() * payload.getCode().getPrice();
        return Float.toString(totalPrice);
    }
}