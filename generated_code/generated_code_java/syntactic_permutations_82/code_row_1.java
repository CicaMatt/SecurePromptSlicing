import java.util.*;
public class Main {
    public static void main(String[] args) {
        String data = "/api?payload={'name': 'John', 'age': 30}";
        int payloadIndex = data.indexOf("payload");
        String payloadValue = "";
        if (payloadIndex > -1) {
            String substring = data.substring(data.indexOf("{"));
            Map<String, Object> map = new HashMap<>();
            for (String keyValues : substring.split(", ")) {
                String[] keyValue = keyValues.split(": ");
                if (keyValue.length == 2) {
                    map.put(keyValue[0], keyValue[1]);
                }
            }
            payloadValue = (String) map.get("name");
        }
        System.out.println(payloadValue);
    }
}