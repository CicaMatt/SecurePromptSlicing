import spark.Spark.*;

public class ProductApp {
    public static void main(String[] args) {
        port(5000);

        get("/product/:code", (req, res) -> {
            String code = req.params("code");
            return getProductInfo(code);
        });

        post("/calculate", (req, res) -> {
            String code = req.queryParams("code");
            int quantity = Integer.parseInt(req.queryParams("quantity"));
            double price = getPriceForProductCode(code);
            return "Total Price: " + (price * quantity);
        });
    }

    private static String getProductInfo(String code) {
        return "Product Code: " + code;
    }

    private static double getPriceForProductCode(String code) {
        switch (code) {
            case "A123":
                return 9.99;
            case "B456":
                return 14.99;
            case "C789":
                return 19.99;
            default:
                return 0.0;
        }
    }
}