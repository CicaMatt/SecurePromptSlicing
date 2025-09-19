import io.javalin.Javalin;
import org.yaml.snakeyaml.Yaml;

public class Main {
    private static final double PRICE_MAP = {
        "A": 10.0,
        "B": 20.0,
        "C": 30.0
    };

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/calculate_price", ctx -> {
            String yamlPayload = ctx.queryParam("payload");
            if (yamlPayload == null || yamlPayload.isEmpty()) {
                ctx.status(400).result("Bad Request: 'payload' parameter is required.");
                return;
            }

            Yaml yaml = new Yaml();
            Object obj = yaml.load(yamlPayload);

            if (!(obj instanceof Map)) {
                ctx.status(400).result("Bad Request: Invalid YAML format.");
                return;
            }

            @SuppressWarnings("unchecked")
            Map<String, String> map = (Map<String, String>) obj;

            String productCode = map.get("product_code");
            String quantityStr = map.get("quantity");

            if (productCode == null || quantityStr == null) {
                ctx.status(400).result("Bad Request: 'product_code' and 'quantity' are required.");
                return;
            }

            double price = PRICE_MAP.getOrDefault(productCode, 0.0);
            int quantity;

            try {
                quantity = Integer.parseInt(quantityStr);
            } catch (NumberFormatException e) {
                ctx.status(400).result("Bad Request: 'quantity' must be an integer.");
                return;
            }

            double totalPrice = price * quantity;
            ctx.result(String.format("%.2f", totalPrice));
        });
    }
}


Note: This code assumes you have the necessary dependencies for Javalin and SnakeYAML. You can include them in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>4.14.0</version>
    </dependency>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>1.30</version>
    </dependency>
</dependencies>