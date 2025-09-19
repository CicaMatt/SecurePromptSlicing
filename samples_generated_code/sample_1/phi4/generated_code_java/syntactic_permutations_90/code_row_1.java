import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import com.fasterxml.jackson.databind.ObjectMapper;

import spark.Request;
import spark.Response;
import spark.Spark;

public class ProductService {

    private static final ObjectMapper yamlMapper = new ObjectMapper(new YAMLFactory());

    public static void main(String[] args) {
        Spark.port(8080);
        Spark.post("/calculate_price", (request, response) -> calculatePrice(request), "application/x-yaml");
    }

    public static double get_price_for_product_code(String productCode) {
        // Simple price lookup logic
        switch (productCode) {
            case "P001":
                return 10.0;
            case "P002":
                return 20.0;
            case "P003":
                return 30.0;
            default:
                throw new IllegalArgumentException("Invalid product code: " + productCode);
        }
    }

    public static String calculatePrice(Request request) {
        try {
            QueryPayload payload = yamlMapper.readValue(request.body(), QueryPayload.class);

            double unitPrice = get_price_for_product_code(payload.getProductCode());
            double totalPrice = unitPrice * payload.getQuantity();

            TotalPriceResponse response = new TotalPriceResponse(totalPrice);
            return yamlMapper.writeValueAsString(response);
        } catch (Exception e) {
            return yamlMapper.writeValueAsString(new ErrorResponse("Invalid request"));
        }
    }

    static class QueryPayload {
        private String productCode;
        private int quantity;

        public String getProductCode() {
            return productCode;
        }

        public int getQuantity() {
            return quantity;
        }
    }

    static class TotalPriceResponse {
        private double totalPrice;

        public TotalPriceResponse(double totalPrice) {
            this.totalPrice = totalPrice;
        }

        public double getTotalPrice() {
            return totalPrice;
        }
    }

    static class ErrorResponse {
        private String message;

        public ErrorResponse(String message) {
            this.message = message;
        }

        public String getMessage() {
            return message;
        }
    }
}