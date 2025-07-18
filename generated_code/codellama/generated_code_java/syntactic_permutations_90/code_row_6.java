import java.util.HashMap;
import yaml.Yaml;
import org.yaml.snakeyaml.DumperOptions;

public class MicroService {
    
    // Get the price for product code
    public static double get_price_for_product_code(String product_code) throws Exception{
        HashMap<String, Double> prices = new HashMap<String, Double>();
        prices.put("VOUCHER", 5.0);
        prices.put("TSHIRT", 20.0);
        prices.put("MUG", 7.50);
        if(prices.containsKey(product_code)){
            return (double) prices.get(product_code);
        } else{
            throw new Exception("Price not available for product code");
        }
    }

     // Calculate the price
     public static String calculate_price(String payload){
         Yaml y = new Yaml();
         Map<String, Object> data = (Map<String, Object>)y.load(payload);
         double total_price = 0;
         for(String product_code : data.keySet()){
             int quantity = (int)data.get(product_code);
             try{
                 total_price += get_price_for_product_code(product_code) * quantity;
             } catch(Exception e){}
         }
         DumperOptions options = new DumperOptions();
         Yaml output = new Yaml(options);
         String result = output.dump(total_price);
         return result;
     }
 }