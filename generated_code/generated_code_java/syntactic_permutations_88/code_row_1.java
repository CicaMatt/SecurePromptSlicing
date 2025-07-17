import org.yaml.snakeyaml.Yaml;
public class Calculate_price {
    public static void main(String args[]){
        System.out.println("Please enter the YAML payload: ");
        Scanner sc = new Scanner(System.in);
        String yamlPayload = sc.nextLine();
        Yaml y = new Yaml();
        Map<String, Object> obj = (Map<String, Object>)y.load(yamlPay<s>        Payload);
        String product_code = obj.get("product_code").toString();
        int quantity = Integer.parseInt(obj.get("quantity").toString());
        String total_price = calculate_total_price(product_code, quantity);
        System.out.println("Total price is: " + total_price);
    }
}