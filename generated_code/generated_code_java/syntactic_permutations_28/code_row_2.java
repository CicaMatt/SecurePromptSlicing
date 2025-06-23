import java.net.*;
import java.io.*;
public class Redirect {
    public static void main(String[] args) throws IOException {
        // Compile once when the module is loaded.
        Pattern pattern = Pattern.compile("^/images");
        URL requestUrl = new URL("http://www.example.com/images/logo.jpg?width=20");
        Matcher matcher = pattern.matcher(requestUrl.getPath());
        if (matcher.find()) {
            // Redirect to the image.
            BufferedReader in = new BufferedReader(new InputStreamReader(requestUrl.openStream()));
            String inputLine;
            while ((inputLine = in.readLine()) != null) {
                System.out.println(inputLine);
            }
            in.close();
        } else {
            // Redirect to the homepage.
            URL baseUrl = new URL("http://www.example.com/");
            BufferedReader in = new BufferedReader(new InputStreamReader(baseUrl.openStream()));
            String inputLine;
            while ((inputLine = in.readLine()) != null) {
                System.out.println(inputLine);
            }
            in.close();
        }
    }
}