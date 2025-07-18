import java.io.IOException;
import javax.servlet.*;
import com.google.gson.*;
import org.yaml.snakeyaml.*;
import org.yaml.snakeyaml.constructor.*;

public class CalculatePrice implements Servlet {
    private String calculate_price(String payload) throws IOException {
        Yaml yaml = new Yaml(new Constructor(Payload.class));
        Payload data = (Payload) yaml.load(payload);
        String productCode = data.product_code;
        int quantity = data.quantity;
        double pricePerUnit = getPricePerProduct(productCode);
        return Double.toString(pricePerUnit * quantity);
    }
}