import org.yaml.snakeyaml.Yaml;
import org.yaml.snakeyaml.constructor.Constructor;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Map;

public class SimpleWebAPI {

    private static final int PORT = 8080;

    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(PORT);
        System.out.println("Server is listening on port " + PORT);

        while (true) {
            try (Socket socket = serverSocket.accept();
                 BufferedReader input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                 var outputStream = socket.getOutputStream()) {

                String queryParam = input.readLine().split(" ")[1];
                String[] queryParams = queryParam.split("&");
                StringBuilder queryString = new StringBuilder();
                
                for (String param : queryParams) {
                    if (queryString.length() > 0) {
                        queryString.append("&");
                    }
                    queryString.append(param);
                }

                String yamlPayload = parseYamlFromQuery(queryString.toString());
                double totalPrice = calculatePrice(yamlPayload);

                outputStream.write(("Total Price: " + totalPrice).getBytes());
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private static String parseYamlFromQuery(String query) {
        Yaml yaml = new Yaml(new Constructor(Map.class));
        Map<String, Object> dataMap = yaml.load(query);
        
        if (dataMap == null || !dataMap.containsKey("payload")) {
            return "{}";
        }

        Map<String, Object> payload = (Map<String, Object>) dataMap.get("payload");
        String productCode = (String) payload.get("product_code");
        int quantity = (int) payload.get("quantity");

        // Dummy price lookup for demonstration purposes
        double price = getProductPrice(productCode);

        return "{ \"price\": " + price + ", \"quantity\": " + quantity + " }";
    }

    private static double calculatePrice(String yamlPayload) {
        Yaml yaml = new Yaml(new Constructor(Map.class));
        Map<String, Object> dataMap = yaml.load(yamlPayload);

        if (dataMap == null) {
            return 0.0;
        }

        Double price = (Double) dataMap.get("price");
        Integer quantity = (Integer) dataMap.get("quantity");

        return price * quantity;
    }

    private static double getProductPrice(String productCode) {
        // Dummy implementation for demonstration purposes
        switch (productCode) {
            case "A":
                return 10.0;
            case "B":
                return 20.0;
            default:
                return 0.0; // Unknown product code
        }
    }
}