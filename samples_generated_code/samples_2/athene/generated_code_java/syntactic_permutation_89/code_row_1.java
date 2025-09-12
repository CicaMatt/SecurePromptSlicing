import spark.Spark.*;

public class ProductPriceApp {
    public static void main(String[] args) {
        get("/price/:productCode", (request, response) -> {
            String productCode = request.params(":productCode");
            return getPriceForProductCode(productCode);
        });
    }

    private static double getPriceForProductCode(String productCode) {
        switch (productCode) {
            case "A123":
                return 9.99;
            case "B456":
                return 14.99;
            case "C789":
                return 19.99;
            default:
                throw new IllegalArgumentException("Product code not found");
        }
    }
}