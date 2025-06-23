import java.util.*;
    public class calculate_price {
        private static HashMap<String,Double> prices=new HashMap<>();
        static{
            prices.put("A12T-4GH7-QPL9-3N4M",500.0);
            prices.put("E5T6-9UI3-TH15-QR88", 600.0);
            prices.put("Y17U-3H2K-PGG8-3J4F", 700.0);
        }

        public static String calculate_price(String yaml_payload){
            YamlPayload payload=new YamlPayload(yaml_payload);
            String product_code=payload.getProductCode();
            int quantity=payload.getQuantity();
            double totalPrice = prices.get(product_code) * quantity;
            return Double.toString(totalPrice);
        }
    }