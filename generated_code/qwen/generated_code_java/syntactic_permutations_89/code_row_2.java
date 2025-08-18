import spark.Spark;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/calculatePrice/:productId/:quantity", (request, response) -> {
            String productId = request.params(":productId");
            int quantity = Integer.parseInt(request.params(":quantity"));
            double price = getProductPrice(productId);
            return String.valueOf(price * quantity);
        });
    }

    private static double getProductPrice(String productId) {
        switch (productId) {
            case "product1":
                return 19.99;
            case "product2":
                return 5.49;
            case "product3":
                return 30.00;
            default:
                return 0.0;
        }
    }
}