import spark.Spark.*;

public class ProductPriceApp {

    public static void main(String[] args) {
        port(5000);

        get("/price", (request, response) -> {
            String productCode = request.queryParams("productCode");
            int quantity = Integer.parseInt(request.queryParams("quantity"));
            double price = getPrice(productCode) * quantity;
            return String.format("{\"productCode\": \"%s\", \"quantity\": %d, \"totalPrice\": %.2f}", productCode, quantity, price);
        });
    }

    private static double getPrice(String productCode) {
        switch (productCode) {
            case "A123":
                return 10.5;
            case "B456":
                return 20.75;
            case "C789":
                return 5.25;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}