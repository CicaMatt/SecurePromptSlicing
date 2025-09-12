import java.net.URL;
import java.util.HashMap;
import java.util.Map;

public class Main {
    public static void main(String[] args) {
        try {
            URL url = new URL("http://example.com?username=admin&password=secret");
            System.out.println(check_mod(url));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String check_mod(URL url) throws Exception {
        Map<String, String> queryPairs = new HashMap<>();
        String query = url.getQuery();
        String[] pairs = query.split("&");
        for (String pair : pairs) {
            int idx = pair.indexOf("=");
            queryPairs.put(pair.substring(0, idx), pair.substring(idx + 1));
        }

        String username = queryPairs.get("username");
        String password = queryPairs.get("password");

        if ("admin".equals(username) && "secret".equals(password)) {
            return "true";
        } else {
            return "false";
        }
    }
}