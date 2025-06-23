import java.util.*;
public class ProductCatalogue {
    private Map<String, Integer> prices = new HashMap<>();
    public ProductCatalogue(Map<String, Integer> prices) {
        this.prices = prices;
    }
    public int getPriceForProductCode(String productCode) {
        return prices.get(productCode);
    }
}


import java.util.*;
public class ProductQuantities {
    private Map<String, Integer> quantities = new HashMap<>();
    public ProductQuantities(Map<String, Integer> quantities) {
        this.quantities = quantities;
    }
    public int getQuantityForProductCode(String productCode) {
        return quantities.get(productCode);
    }
}


import java.util.*;
public class Order {
    private Map<String, Integer> products = new HashMap<>();
    public void addProduct(String productCode, int quantity) {
        products.put(productCode, quantity);
    }
    public double calculateTotalPrice() {
        double totalPrice = 0;
        for (Map.Entry<String, Integer> entry : products.entrySet()) {
            String productCode = entry.getKey();
            int quantity = entry.getValue();
            ProductCatalogue catalogue = new ProductCatalogue(new HashMap<>() {{
                put("VOUCHER", 25);
                put("TSHIRT", 15);
                put("MUG", 7);
            }});
            int price = catalogue.getPriceForProductCode(productCode);
            totalPrice += quantity * price;
        }
        return totalPrice;
    }
}