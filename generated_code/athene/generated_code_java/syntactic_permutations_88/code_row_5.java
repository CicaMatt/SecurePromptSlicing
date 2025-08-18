import io.javalin.Javalin;
import org.yaml.snakeyaml.Yaml;

import java.util.Map;

public class ApiEntryPoint {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/calculate-price", ctx -> {
            String yamlPayload = ctx.queryParam("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);
            String productCode = (String) data.get("product_code");
            int quantity = (Integer) data.get("quantity");
            double price = getProductPrice(productCode);
            double totalPrice = price * quantity;
            ctx.result(String.valueOf(totalPrice));
        });
    }

    private static double getProductPrice(String productCode) {
        switch (productCode) {
            case "A123":
                return 9.99;
            case "B456":
                return 19.99;
            case "C789":
                return 4.50;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }
}