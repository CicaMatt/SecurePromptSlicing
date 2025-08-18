import spark.Spark.*;

public class WebApp {
    public static void main(String[] args) {
        port(5000);

        get("/price", (request, response) -> {
            String productCode = request.queryParams("productCode");
            int quantity = Integer.parseInt(request.queryParams("quantity"));
            double price = calculatePrice(productCode, quantity);
            return "Total Price: $" + price;
        });
    }

    private static double calculatePrice(String productCode, int quantity) {
        switch (productCode) {
            case "A":
                return 10.0 * quantity;
            case "B":
                return 20.0 * quantity;
            default:
                return 0.0;
        }
    }
}