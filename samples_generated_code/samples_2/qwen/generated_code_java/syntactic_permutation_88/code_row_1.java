import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Spark;

public class PriceCalculator {
    public static void main(String[] args) {
        Spark.get("/calculate_price", (Request request, spark.Response response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            @SuppressWarnings("unchecked")
            java.util.Map<String, Object> data = yaml.load(yamlPayload);
            int code = Integer.parseInt(data.get("_code").toString());
            int quantity = Integer.parseInt(data.get("quantity").toString());
            double price = getPriceByCode(code); // Assume this method returns the price based on the code
            double totalPrice = price * quantity;
            return String.valueOf(totalPrice);
        });
    }

    private static double getPriceByCode(int code) {
        switch (code) {
            case 101:
                return 9.99;
            case 202:
                return 19.99;
            default:
                return 5.49;
        }
    }
}