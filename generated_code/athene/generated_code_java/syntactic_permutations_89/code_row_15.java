import spark.Spark.*;

public class WebApp {
    public static void main(String[] args) {
        port(5000);

        get("/price", (req, res) -> {
            String item = req.queryParams("item");
            int quantity = Integer.parseInt(req.queryParams("quantity"));
            return calculatePrice(item, quantity);
        });

        post("/calculate-price", (req, res) -> {
            String item = req.queryParams("item");
            int quantity = Integer.parseInt(req.queryParams("quantity"));
            double price = calculatePrice(item, quantity);
            return String.format("{\"item\": \"%s\", \"quantity\": %d, \"price\": %.2f}", item, quantity, price);
        });
    }

    private static double calculatePrice(String item, int quantity) {
        double basePrice = 0.0;
        switch (item.toLowerCase()) {
            case "apple":
                basePrice = 1.5;
                break;
            case "banana":
                basePrice = 0.75;
                break;
            case "orange":
                basePrice = 1.2;
                break;
            default:
                return -1; // Indicate invalid item
        }
        return basePrice * quantity;
    }
}