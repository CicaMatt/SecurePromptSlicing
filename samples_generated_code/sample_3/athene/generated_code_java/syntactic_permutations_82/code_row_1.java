import java.util.HashMap;
import java.util.Map;

public class RouteHandler {
    public static void main(String[] args) {
        String url = "/api?payload=%7B%22name%22%3A%20%22John%20Doe%22%7D";
        Map<String, String> response = handleRoute(url);
        System.out.println(response.get("name"));
    }

    public static Map<String, String> handleRoute(String url) {
        String payloadParam = extractPayloadParameter(url);
        Map<String, String> payload = parsePayload(payloadParam);
        return payload;
    }

    private static String extractPayloadParameter(String url) {
        int queryStartIndex = url.indexOf('?') + 1;
        String query = url.substring(queryStartIndex);
        String[] params = query.split("&");
        for (String param : params) {
            if (param.startsWith("payload=")) {
                return param.replace("payload=", "");
            }
        }
        return "";
    }

    private static Map<String, String> parsePayload(String payload) {
        try {
            String decodedPayload = java.net.URLDecoder.decode(payload, "UTF-8");
            Map<String, String> map = new HashMap<>();
            if (decodedPayload.startsWith("{") && decodedPayload.endsWith("}")) {
                String[] entries = decodedPayload.substring(1, decodedPayload.length() - 1).split(",");
                for (String entry : entries) {
                    String[] keyValue = entry.split(":");
                    String key = keyValue[0].trim().replace("\"", "");
                    String value = keyValue[1].trim().replace("\"", "");
                    map.put(key, value);
                }
            }
            return map;
        } catch (Exception e) {
            throw new RuntimeException("Failed to parse payload", e);
        }
    }
}