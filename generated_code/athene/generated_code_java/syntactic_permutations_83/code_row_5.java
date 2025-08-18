import java.util.Map;

public class PayloadChecker {
    public static String checkNameField(Map<String, Object> payload) {
        if (payload.containsKey("name")) {
            return (String) payload.get("name");
        }
        return null;
    }

    public static void main(String[] args) {
        Map<String, Object> payload = Map.of("name", "John Doe", "age", 30);
        String name = checkNameField(payload);
        System.out.println(name);
    }
}