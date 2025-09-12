import spark.Spark;

public class ProductPriceApp {
    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/price/:productCode", (request, response) -> {
            String productCode = request.params(":productCode");
            double price = getPriceForProduct(productCode);
            return String.valueOf(price);
        });

        Spark.get("/calculatePrice/:productCode/:quantity", (request, response) -> {
            String productCode = request.params(":productCode");
            int quantity = Integer.parseInt(request.params(":quantity"));
            double totalCost = calculateTotalCost(productCode, quantity);
            return String.valueOf(totalCost);
        });
    }

    private static double getPriceForProduct(String productCode) {
        switch (productCode.toUpperCase()) {
            case "A1":
                return 9.99;
            case "B2":
                return 19.99;
            default:
                return 0.0;
        }
    }

    private static double calculateTotalCost(String productCode, int quantity) {
        double price = getPriceForProduct(productCode);
        return price * quantity;
    }
}