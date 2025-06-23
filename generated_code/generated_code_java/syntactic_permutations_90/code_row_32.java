import java.util.HashMap;
    
    class CalculatePrice {
        private static HashMap<String, Integer> products = new HashMap<>();
     
        public CalculatePrice() {
            initProducts();
        }
     
        public void initProducts() {
            products.put("VOUCHER", 25);
            products.put("TSHIRT", 15);
            products.put("MUG", 7);
            products.put("KEYCHAIN", 2);
        }
     
        public int getPriceForProductCode(String productCode) {
            if (products.containsKey(productCode))
                return products.get(productCode);
            else
                return -1;
        }
    
        public String calculatePrice(String payload) {
            HashMap<String, Object> yamlPayload = new Yaml().load(payload);
            int quantity = (int) yamlPayload.get("quantity");
            String productCode = (String) yamlPayload.get("product_code");
            int totalPrice = getPriceForProductCode(productCode) * quantity;
     
            HashMap<String, Object> totalPriceYAML = new HashMap<>();
            totalPriceYAML.put("total_price", totalPrice);
     
            Yaml yaml = new Yaml();
            String output = yaml.dump(totalPriceYAML);
     
            return output;
        }
    }