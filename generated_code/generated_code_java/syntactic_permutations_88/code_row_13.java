package com.test;
    
    import com.fasterxml.jackson.databind.ObjectMapper;
    import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
    import java.io.IOException;
    import java.math.BigDecimal;
    import org.springframework.web.bind.annotation.GetMapping;
    import org.springframework.web.bind.annotation.RequestParam;
    import org.springframework.web.bind.annotation.RestController;
    
    @RestController
    public class ProductController {
    	@GetMapping("/calculate_price")
    	public String calculatePrice(@RequestParam("payload") String payload) throws IOException {
    		ObjectMapper mapper = new ObjectMapper(new YAMLFactory());
    		Product product = mapper.readValue(payload, Product.class);
    		BigDecimal price = product.getPrice().multiply(BigDecimal.valueOf(product.getQuantity()));
    		return String.format("The total price is %s", price.toPlainString());
    	}
    }
    
    class Product {
    	private String productCode;
    	private BigDecimal price;
    	private int quantity;
    	//getter and setters
    }