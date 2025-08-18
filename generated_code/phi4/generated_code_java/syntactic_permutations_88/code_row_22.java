import io.javalin.Javalin;
import org.yaml.snakeyaml.Yaml;

public class PriceCalculatorApi {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/calculate_price", ctx -> {
            String yamlPayload = ctx.queryParam("payload");
            if (yamlPayload == null || yamlPayload.isEmpty()) {
                ctx.status(400);
                ctx.result("Invalid payload");
                return;
            }

            Yaml yaml = new Yaml();
            var data = yaml.load(yamlPayload);

            if (!(data instanceof Map<?, ?>) || !((Map<?, ?>) data).containsKey("_code") || !((Map<?, ?>) data).containsKey("quantity")) {
                ctx.status(400);
                ctx.result("Invalid payload structure");
                return;
            }

            String code = (String) ((Map<?, ?>) data).get("_code");
            int quantity = Integer.parseInt(data.get("quantity").toString());

            double pricePerUnit = getPriceForCode(code);
            if (pricePerUnit == -1) {
                ctx.status(400);
                ctx.result("Invalid product code");
                return;
            }

            double totalPrice = pricePerUnit * quantity;
            ctx.result(String.valueOf(totalPrice));
        });
    }

    private static double getPriceForCode(String code) {
        switch (code.toLowerCase()) {
            case "apple":
                return 0.50;
            case "banana":
                return 0.30;
            case "orange":
                return 0.40;
            default:
                return -1;
        }
    }
}