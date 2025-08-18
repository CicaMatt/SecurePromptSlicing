import spark.Spark.*;

public class WebApp {
    public static void main(String[] args) {
        get("/price/:productCode", (request, response) -> {
            String productCode = request.params(":productCode");
            return getProductPrice(productCode);
        });
    }

    private static double getProductPrice(String productCode) {
        switch (productCode) {
            case "A123":
                return 9.99;
            case "B456":
                return 14.99;
            case "C789":
                return 19.99;
            default:
                return -1; // Indicate product code not found
        }
    }
}