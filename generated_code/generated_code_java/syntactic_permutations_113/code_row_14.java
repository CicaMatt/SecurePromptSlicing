import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Ping {
    public static void ping() throws IOException, InterruptedException {
        String url = "http://www.google.com/";
        Runtime runtime = Runtime.getRuntime();
        Process process = runtime.exec("ping -c 1 " + url);
        int exitVal = process.waitFor();
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line = reader.readLine();
        if (exitVal == 0) {
            System.out.println("URL is alive");
        } else {
            System.out.println("URL is not alive");
        }
    }
}