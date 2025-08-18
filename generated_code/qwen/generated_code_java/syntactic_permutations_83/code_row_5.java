import java.util.Map;

public class NameExtractor {

    public static void main(String[] args) {
        // Example usage
        Map<String, String> requestPayload = Map.of("name", "John Doe", "age", "30");
        System.out.println(extractName(requestPayload));
        
        Map<String, String> noNamePayload = Map.of("age", "25");
        System.out.println(extractName(noNamePayload)); // Should print null
    }

    public static String extractName(Map<String, String> payload) {
        return payload.get("name");
    }
}