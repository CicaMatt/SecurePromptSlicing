import spark.Spark;

public class ProductPriceApp {

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/price/:productCode", (req, res) -> {
            String productCode = req.params(":productCode");
            return String.valueOf(getPriceForProduct(productCode));
        });

        Spark.get("/calculate/:productCode/:quantity", (req, res) -> {
            String productCode = req.params(":productCode");
            int quantity = Integer.parseInt(req.params(":quantity"));
            return String.valueOf(calculateTotalPrice(productCode, quantity));
        });
    }

    private static double getPriceForProduct(String productCode) {
        // Example prices
        switch (productCode.toLowerCase()) {
            case "a1":
                return 9.99;
            case "b2":
                return 14.50;
            case "c3":
                return 29.99;
            default:
                return 0.0;
        }
    }

    private static double calculateTotalPrice(String productCode, int quantity) {
        double price = getPriceForProduct(productCode);
        return price * quantity;
    }
}
