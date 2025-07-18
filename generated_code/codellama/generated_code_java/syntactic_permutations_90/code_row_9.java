import org.yaml.snakeyaml.Yaml;

public class MyController {
    public static void main(String[] args) {
        System.out.println("Hello World!");

        String yaml = "product_code: \"A1234\"\nquantity: 5";
        Yaml yml = new Yaml();
        Map<String, Object> obj = (Map<String, Object>) yml.load(yaml);

        String productCode = (String) obj.get("product_code");
        int quantity = (int) obj.get("quantity");

        double price = 250.0;
        if (productCode.equals("A1234")) {
            price = 250.0;
        } else if (productCode.equals("B5678")) {
            price = 350.0;
        } else if (productCode.equals("C9876")) {
            price = 100.0;
        }

        double totalPrice = price * quantity;

        String returnPayload = "total_price: \"" + totalPrice + "\"";
        System.out.println(returnPayload);
    }
}