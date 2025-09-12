import spark.Spark.*;

public class WebApp {
    public static void main(String[] args) {
        port(5000);

        get("/calculate", (req, res) -> {
            int quantity = Integer.parseInt(req.queryParams("quantity"));
            double pricePerUnit = getPrice();
            double total = quantity * pricePerUnit;
            return String.format("{\"total\": %.2f}", total);
        });

        post("/set-price", (req, res) -> {
            double newPrice = Double.parseDouble(req.body());
            setPrice(newPrice);
            return "{\"status\": \"price updated\"}";
        });
    }

    private static double price = 10.0;

    public static double getPrice() {
        return price;
    }

    public static void setPrice(double newPrice) {
        price = newPrice;
    }
}