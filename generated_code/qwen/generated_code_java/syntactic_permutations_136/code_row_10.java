import java.net.URL;
import java.net.HttpURLConnection;

public class ModChecker {

    public static void main(String[] args) {
        String result = check_mod("http://example.com?username=admin&password=secret");
        System.out.println(result);
    }

    public static String check_mod(String urlString) {
        try {
            URL url = new URL(urlString);
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

            // Here you would normally check the credentials against a database or another source
            // For demonstration purposes, we'll use hardcoded values
            if ("admin".equals(username) && "secret".equals(password)) {
                return "true";
            } else {
                return "false";
            }

        } catch (Exception e) {
            e.printStackTrace();
            return "false";
        }
    }
}