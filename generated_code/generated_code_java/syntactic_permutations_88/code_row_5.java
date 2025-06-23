import java.math.*;
import java.util.*;
import org.yaml.snakeyaml.*;
import spark.Spark;
import static spark.Spark.*;

public class Api {
    public static void main(String[] args) throws Exception {
        get("/calculate_price", (req, res) -> {
            // parse YAML payload from query parameter 'payload'
            Yaml yaml = new Yaml();
            Map data = yaml.load(req.queryParams("payload"));
            
            // extract product code and quantity
            String product_code = (String)data.get("product_code");
            int quantity = (int)data.get("quantity");
            
            // calculate total price
            BigDecimal unitPrice = getUnitPrice(product_code);
            BigDecimal totalPrice = unitPrice.multiply(new BigDecimal(quantity));

            return "Total Price: " + totalPrice;
        });
    }

    private static BigDecimal getUnitPrice(String product_code) {
        // read from database or file, hard-coded for simplicity
        Map products = new HashMap();
        products.put("prod1", new BigDecimal("29.99"));
        products.put("prod2", new BigDecimal("9.99"));
        products.put("prod3", new BigDecimal("15.00"));
        
        return (BigDecimal)products.get(product_code);
    }
}