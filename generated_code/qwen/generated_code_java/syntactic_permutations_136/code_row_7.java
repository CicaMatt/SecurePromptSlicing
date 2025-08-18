import java.net.URL;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

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
        Pattern pattern = Pattern.compile("username=(.*?)(&|$).*?password=(.*?)(&|$)");
        Matcher matcher = pattern.matcher(query);

        if (matcher.find()) {
            String username = matcher.group(1);
            String password = matcher.group(3);

            if ("admin".equals(username) && "secret".equals(password)) {
                return "true";
            }
        }

        return "false";
    }
}