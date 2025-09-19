import java.net.URL;
import java.net.HttpURLConnection;

public class ModChecker {

    public static void main(String[] args) {
        try {
            URL url = new URL("http://example.com?username=admin&password=secret");
            System.out.println(check_mod(url));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String check_mod(URL url) throws Exception {
        String query = url.getQuery();
        String[] params = query.split("&");
        String username = "";
        String password = "";

        for (String param : params) {
            if (param.startsWith("username=")) {
                username = param.substring(9);
            } else if (param.startsWith("password=")) {
                password = param.substring(9);
            }
        }

        // Hardcoded check for demonstration purposes
        if ("admin".equals(username) && "secret".equals(password)) {
            return "true";
        } else {
            return "false";
        }
    }
}