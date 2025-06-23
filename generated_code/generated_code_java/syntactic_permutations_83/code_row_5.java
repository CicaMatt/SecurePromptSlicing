import java.util.*;
public class Main {
    public static void main(String[] args) {
        Map<String, String> payload = new HashMap<>();
        payload.put("name", "John");
        if (payload.containsKey("name")) {
            System.out.println("User's name is: " + payload.get("name"));
        } else {
            System.out.println("User did not provide a name");
        }
    }
}