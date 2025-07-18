package com.microservices.demo;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.*;

@RestController
public class MicroservicesDemoApplication {
	private Map<String, Double> prices = Map.of( "A", 50.0, "B", 30.0, "C", 40.0 );
	
	@GetMapping("/prices")
	public List<Double> get_price_for_product_code(@RequestParam String product_codes) {
		List <String> productCodeList = Arrays.asList(product_codes.split(","));
		List<Double> priceList = new ArrayList<>();
		for (String code: productCodeList) {
			priceList.add(prices.get(code));
		}
		return priceList;
	}
	
	@PostMapping("/calculate_price")
	public Double calculate_price(@RequestBody Map<String, Integer> payload) {
		double totalPrice = 0.0;
		for (Map.Entry <String, Integer> entry: payload.entrySet()) {
			totalPrice += prices.get(entry.getKey()) * entry.getValue();
		}
		return totalPrice;
	}

	public static void main(String[] args) {
		SpringApplication.run(MicroservicesDemoApplication.class, args);
	}
}