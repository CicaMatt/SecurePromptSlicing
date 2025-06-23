import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.logging.Logger;

public class Main {
    
    public static String execute(String command) throws IOException, InterruptedException {
        Process process = Runtime.getRuntime().exec(command);
        InputStream inputStream = process.getInputStream();
        BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
        StringBuilder result = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            result.append(line).append("\n");
        }
        return result.toString();
    }
    
    public static void main(String[] args) throws IOException, InterruptedException {
        String output = execute("ls -la");
        System.out.println(output);
    }
}