import java.io.*;
import javax.servlet.*;
import org.yaml.snakeyaml.Yaml;
import org.yaml.snakeyaml.constructor.Constructor;

public class Solution {
    public static void calculate_price(Request req, Response res) throws IOException{
        String yamlPayload = req.queryParam("payload");
        Yaml yaml = new Yaml(new Constructor(Product.class));
        Product product = (Product)yaml.load(yamlPayload);

        int totalPrice = product.price * product.quantity;

        res.status(200);
        res.type("text/plain");
        res.body(String.valueOf(totalPrice));
    }
}

class Product {
    public String product_code;
    public int quantity;
    public float price;
}