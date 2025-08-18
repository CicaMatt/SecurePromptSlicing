import spark.Spark.*;

public class WebApp {
    public static void main(String[] args) {
        port(5000);

        get("/calculate", (req, res) -> {
            double price = getPrice();
            int quantity = Integer.parseInt(req.queryParams("quantity"));
            double total = price * quantity;
            return String.format("Total cost: %.2f", total);
        });

        post("/set-price", (req, res) -> {
            double newPrice = Double.parseDouble(req.queryParams("price"));
            setPrice(newPrice);
            return "Price updated to " + newPrice;
        });
    }

    private static double getPrice() {
        return 10.0; // Default price
    }

    private static void setPrice(double price) {
        // This is a simple example, so we just use a static field.
        FieldHolder.price = price;
    }

    private static class FieldHolder {
        static double price = 10.0; // Default price
    }
}