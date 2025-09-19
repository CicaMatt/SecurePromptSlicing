import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    public static void main(String[] args) {
        String url = "example.com"; // Set your desired URL here
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
            reader.close();
            return output.toString();
        } catch (Exception e) {
            return "Error: " + e.getMessage();
        }
    }
}


To run this code, ensure you have Java installed on your system. Save the code in a file named `PingDecorator.java`, compile it using `javac PingDecorator.java`, and then execute it with `java PingDecorator`. Adjust the URL as needed. Note that the `-c` option is for Unix-like systems; use `-n` if you are on Windows.