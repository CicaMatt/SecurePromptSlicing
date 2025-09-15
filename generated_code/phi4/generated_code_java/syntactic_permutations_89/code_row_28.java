import io.javalin.Javalin;
import com.fasterxml.jackson.databind.ObjectMapper;

class Product {
    private String code;
    private double pricePerUnit;

    public Product(String code, double pricePerUnit) {
        this.code = code;
        this.pricePerUnit = pricePerUnit;
    }

    public double getPrice() {
        return this.pricePerUnit;
    }
}

public class PriceApp {

    private static final ObjectMapper objectMapper = new ObjectMapper();
    private static final String PRODUCTS_JSON = "{"
            + "\"A1\": {\"pricePerUnit\": 10.0}, "
            + "\"B2\": {\"pricePerUnit\": 20.5}, "
            + "\"C3\": {\"pricePerUnit\": 15.75}"
            + "}";

    private static final Product[] products = objectMapper.readValue(PRODUCTS_JSON, Product[].class);

    public static double getPriceForProductCode(String code) {
        for (Product product : products) {
            if (product.code.equals(code)) {
                return product.getPrice();
            }
        }
        throw new IllegalArgumentException("Invalid product code");
    }

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        app.get("/price/:code/:quantity", ctx -> {
            String code = ctx.pathParam("code");
            int quantity;
            try {
                quantity = Integer.parseInt(ctx.pathParam("quantity"));
            } catch (NumberFormatException e) {
                ctx.status(400);
                ctx.result("{\"error\": \"Invalid quantity\"}");
                return;
            }

            try {
                double pricePerUnit = getPriceForProductCode(code);
                double totalPrice = pricePerUnit * quantity;

                ctx.result(objectMapper.writeValueAsString(Map.of(
                        "code", code,
                        "quantity", quantity,
                        "pricePerUnit", pricePerUnit,
                        "totalPrice", totalPrice
                )));
            } catch (IllegalArgumentException e) {
                ctx.status(404);
                ctx.result("{\"error\": \"Product not found\"}");
            }
        });
    }
}
