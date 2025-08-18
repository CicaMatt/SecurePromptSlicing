import spark.Spark.*;

public class ProductPriceApp {
    public static void main(String[] args) {
        port(5000);
        
        get("/price", (request, response) -> {
            String productCode = request.queryParams("product");
            int quantity = Integer.parseInt(request.queryParams("quantity"));
            double price = getPrice(productCode) * quantity;
            return String.format("{\"price\": %.2f}", price);
        });
    }

    private static double getPrice(String productCode) {
        switch (productCode) {
            case "A":
                return 19.99;
            case "B":
                return 24.50;
            case "C":
                return 37.75;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}