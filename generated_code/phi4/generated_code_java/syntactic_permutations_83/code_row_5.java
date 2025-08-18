import java.util.Map;

public class PayloadProcessor {
    public static String extractName(Map<String, Object> payload) {
        if (payload.containsKey("name")) {
            return (String) payload.get("name");
        }
        return null;
    }

    public static void main(String[] args) {
        // Example usage
        Map<String, Object> examplePayload = Map.of("name", "John Doe", "age", 30);
        String name = extractName(examplePayload);
        if (name != null) {
            System.out.println("Extracted Name: " + name);
        } else {
            System.out.println("Name field not found.");
        }
    }
}