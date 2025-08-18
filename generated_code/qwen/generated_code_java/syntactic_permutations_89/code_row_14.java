import spark.Spark;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.port(5000);
        
        Spark.get("/calculate", (req, res) -> {
            String priceParam = req.queryParams("price");
            String quantityParam = req.queryParams("quantity");

            if (priceParam == null || quantityParam == null) {
                return "Please provide both 'price' and 'quantity' parameters.";
            }

            double price = Double.parseDouble(priceParam);
            int quantity = Integer.parseInt(quantityParam);

            double totalPrice = calculateTotalPrice(price, quantity);

            res.type("application/json");
            return "{\"totalPrice\": " + totalPrice + "}";
        });
    }

    public static double calculateTotalPrice(double price, int quantity) {
        return price * quantity;
    }
}