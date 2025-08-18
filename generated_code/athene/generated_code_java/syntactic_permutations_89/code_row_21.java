import spark.Spark.*;

public class ProductApp {
    public static void main(String[] args) {
        port(5000);

        get("/product/:code", (req, res) -> {
            String code = req.params("code");
            return getProductPrice(code);
        });

        post("/calculate/:code/:quantity", (req, res) -> {
            String code = req.params("code");
            int quantity = Integer.parseInt(req.params("quantity"));
            double price = getProductPrice(code);
            return price * quantity;
        });
    }

    private static double getProductPrice(String code) {
        switch (code) {
            case "A123":
                return 10.50;
            case "B456":
                return 20.75;
            case "C789":
                return 30.00;
            default:
                return -1; // Indicate invalid product code
        }
    }
}