import java.io.*;

public class PingDecorator {
    public static String ping(String url) throws IOException {
        String output = "";
        if (url != null) {
            Process process = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                output += line;
            }
        } else {
            return "No valid URL was provided.";
        }
        return output;
    }
}