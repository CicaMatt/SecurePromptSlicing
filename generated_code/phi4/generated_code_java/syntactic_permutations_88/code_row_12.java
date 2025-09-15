import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.IOException;
import java.util.Optional;

public class PriceCalculator {

    public static void main(String[] args) {
        String yamlPayload = "items:\n  - name: item1\n    price: 10.0\n    quantity: 2\n  - name: item2\n    price: 20.0\n    quantity: 5";

        try {
            double totalPrice = calculatePrice(yamlPayload);
            System.out.println("Total Price: " + totalPrice);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static double calculatePrice(String yamlPayload) throws IOException {
        ObjectMapper mapper = new ObjectMapper(new YAMLFactory());
        JsonNode rootNode = mapper.readTree(yamlPayload);

        double total = 0.0;
        if (rootNode.has("items")) {
            for (JsonNode item : rootNode.path("items")) {
                Optional<Double> priceOpt = Optional.ofNullable(item.get("price")).map(JsonNode::asDouble);
                Optional<Integer> quantityOpt = Optional.ofNullable(item.get("quantity")).map(JsonNode::asInt);

                if (priceOpt.isPresent() && quantityOpt.isPresent()) {
                    double price = priceOpt.get();
                    int quantity = quantityOpt.get();
                    total += price * quantity;
                }
            }
        }

        return total;
    }
}
