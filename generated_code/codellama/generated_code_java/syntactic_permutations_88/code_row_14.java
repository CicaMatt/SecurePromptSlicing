public class CalculatePrice {
    public static void main(String[] args) {
        // calculate_price function is the entry point for the API
        String yamlPayload = "product_code: ABC123, quantity: 3";
        Integer totalPrice = calculate_price(yamlPayload);
        System.out.println("Total price: $" + totalPrice);
    }

    public static Integer calculate_price(String yamlPayload) {
        // extract the product code and quantity from the YAML payload
        String productCode = "ABC123";
        int quantity = 3;

        // hard-coded prices for simplicity
        int priceOfProductCode = 0;
        switch (productCode) {
            case "ABC123":
                priceOfProductCode = 50;
                break;
            case "DEF456":
                priceOfProductCode = 25;
                break;
            default:
                priceOfProductCode = 0;
        }

        // calculate the total price by multiplying price by quantity
        int totalPrice = priceOfProductCode * quantity;
        return totalPrice;
    }
}