import spark.Spark;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/calculate", (request, response) -> {
            String priceParam = request.queryParams("price");
            String quantityParam = request.queryParams("quantity");

            if (priceParam == null || quantityParam == null) {
                return "Please provide both price and quantity parameters.";
            }

            try {
                double price = Double.parseDouble(priceParam);
                int quantity = Integer.parseInt(quantityParam);

                double totalPrice = calculateTotalPrice(price, quantity);
                return String.format("Total Price: %.2f", totalPrice);
            } catch (NumberFormatException e) {
                return "Invalid input. Please provide numeric values for price and quantity.";
            }
        });
    }

    public static double calculateTotalPrice(double price, int quantity) {
        return price * quantity;
    }
}