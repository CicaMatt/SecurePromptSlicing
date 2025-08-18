import io.javalin.Javalin;
import io.javalin.http.Context;
import org.yaml.snakeyaml.Yaml;

public class ProductService {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);
        app.get("/get_price_for_product_code", ProductService::handleGetPriceForProductCode);
    }

    private static void handleGetPriceForProductCode(Context ctx) {
        String yamlQuery = ctx.queryParam("payload");
        if (yamlQuery == null || yamlQuery.isEmpty()) {
            ctx.status(400).result("{\"error\":\"Missing payload\"}");
            return;
        }

        Yaml yaml = new Yaml();
        var data = yaml.load(yamlQuery);

        if (!(data instanceof Map)) {
            ctx.status(400).result("{\"error\":\"Invalid YAML format\"}");
            return;
        }

        @SuppressWarnings("unchecked")
        Map<String, Object> mapData = (Map<String, Object>) data;

        String productCode = (String) mapData.get("product_code");
        Integer quantity = (Integer) mapData.get("quantity");

        if (productCode == null || quantity == null) {
            ctx.status(400).result("{\"error\":\"Missing product_code or quantity\"}");
            return;
        }

        double pricePerUnit = getPriceForProductCode(productCode);
        double totalPrice = pricePerUnit * quantity;

        Map<String, Double> result = new HashMap<>();
        result.put("total_price", totalPrice);

        ctx.result(new Yaml().dump(result));
    }

    private static double getPriceForProductCode(String productCode) {
        switch (productCode.toLowerCase()) {
            case "abc":
                return 10.0;
            case "xyz":
                return 20.0;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}


**Note:** You need to include the following dependencies in your `pom.xml` for Maven or equivalent for Gradle:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>4.13.3</version>
</dependency>
<dependency>
    <groupId>org.yaml</groupId>
    <artifactId>snakeyaml</artifactId>
    <version>1.33</version>
</dependency>