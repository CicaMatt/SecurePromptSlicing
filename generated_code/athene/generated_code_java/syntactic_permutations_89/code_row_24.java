import spark.Spark.*;

public class PriceCalculatorApp {
    public static void main(String[] args) {
        port(5000);

        get("/price", (req, res) -> {
            String item = req.queryParams("item");
            int quantity = Integer.parseInt(req.queryParams("quantity"));
            double price = getPrice(item) * quantity;
            return String.format("{ \"item\": \"%s\", \"quantity\": %d, \"total_price\": %.2f }", item, quantity, price);
        });

    }

    private static double getPrice(String item) {
        switch (item.toLowerCase()) {
            case "apple":
                return 0.5;
            case "banana":
                return 0.3;
            default:
                return 1.0; // Default price
        }
    }
}