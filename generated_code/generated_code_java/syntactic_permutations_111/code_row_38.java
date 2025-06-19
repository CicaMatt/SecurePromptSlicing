import java.io.*;
import java.net.*;

public class Ping {
    public static void main(String[] args) throws Exception {
        URL url = new URL("https://www.google.com");
        System.out.println(ping(url));
    }

    private static String ping(URL url) throws IOException, InterruptedException {
        ProcessBuilder builder = new ProcessBuilder();
        builder.command("ping", "-c 3", url.getHost());
        Process process = builder.start();
        StringBuilder output = new StringBuilder();
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            output.append(line + "\n");
        }
        int exitVal = process.waitFor();
        if (exitVal == 0) {
            return output.toString();
        } else {
            throw new RuntimeException("ping command failed with status: " + exitVal);
        }
    }
}