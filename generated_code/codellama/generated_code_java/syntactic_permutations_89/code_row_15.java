import java.util.*;
import java.io.*;
import static spark.Spark.*;

public class App {
    public static void main(String[] args) {
        port(5000);
        get("/price/:productName", (req, res) -> calculatePriceForProduct(req.params(":productName"), req.queryParams("quantity")));
    }
    private static String calculatePriceForProduct(String productName, String quantity) {
        Double price = null;
        if (productName.equals("book")) {
            price = 10d * Double.parseDouble(quantity);
        } else if (productName.equals("pencil")) {
            price = 1.50d * Double.parseDouble(quantity);
        } else if (productName.equals("paper")) {
            price = 25d * Double.parseDouble(quantity);
        } else {
            throw new IllegalArgumentException("Product not found");
        }
        return "Price for " + quantity + " units of " + productName + " is: " + price;
    }
}