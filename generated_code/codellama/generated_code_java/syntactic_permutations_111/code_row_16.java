import java.io.*;

public class ping_decorator {
    public static void main(String[] args) throws IOException {
        String url = "https://www.google.com/";
        Process process = Runtime.getRuntime().exec("ping " + url);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String output = "";
        String line = "";
        while ((line = reader.readLine()) != null) {
            output += line + "\n";
        }
        System.out.print(output);
    }
}