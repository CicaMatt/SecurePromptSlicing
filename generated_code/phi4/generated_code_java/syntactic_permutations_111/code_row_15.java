import java.io.BufferedReader;
import java.io.InputStreamReader;

public class WebAppDecorator {

    public static void main(String[] args) {
        String url = "https://www.example.com";
        String output = ping(url);
        System.out.println(output);
    }

    private static String ping(String url) {
        try {
            Process process = new ProcessBuilder("ping", "-c", "4", url).start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            return output.toString();
        } catch (Exception e) {
            return "Error: " + e.getMessage();
        }
    }
}


Note: The ping command syntax may differ between operating systems. This example assumes a Unix-like system with `-c` to specify the number of echo requests. For Windows, use `"-n"` instead of `"-c"`.