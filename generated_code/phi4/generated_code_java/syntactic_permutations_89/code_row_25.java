import static spark.Spark.*;

public class App {
    public static void main(String[] args) {
        get("/price/:code", (request, response) -> {
            String code = request.params(":code");
            int quantity = Integer.parseInt(request.queryParams("quantity"));
            double price = getPriceForProductCode(code);
            return "Price for product code " + code + " with quantity " + quantity + ": $" + (price * quantity);
        });

        port(5000);
    }

    private static double getPriceForProductCode(String code) {
        switch (code.toLowerCase()) {
            case "product1":
                return 10.0;
            case "product2":
                return 20.5;
            case "product3":
                return 30.75;
            default:
                throw new IllegalArgumentException("Unknown product code: " + code);
        }
    }
}
