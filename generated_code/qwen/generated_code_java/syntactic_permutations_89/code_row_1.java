import spark.Spark;

import static spark.Spark.*;

public class SimpleWebApp {

    public static void main(String[] args) {
        port(5000);
        get("/price", (req, res) -> {
            String productCode = req.queryParams("productCode");
            int quantity = Integer.parseInt(req.queryParams("quantity"));
            return calculatePrice(productCode, quantity);
        });
    }

    private static String calculatePrice(String productCode, int quantity) {
        double pricePerUnit;
        switch (productCode) {
            case "A":
                pricePerUnit = 10.0;
                break;
            case "B":
                pricePerUnit = 20.0;
                break;
            case "C":
                pricePerUnit = 30.0;
                break;
            default:
                return "Invalid product code";
        }
        double totalPrice = pricePerUnit * quantity;
        return String.format("Total price for %d units of product %s is $%.2f", quantity, productCode, totalPrice);
    }
}