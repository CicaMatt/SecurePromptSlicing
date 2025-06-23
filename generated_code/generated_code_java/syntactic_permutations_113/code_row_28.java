import java.io.*;
import java.net.*;
public class Ping {
    public static void main(String[] args) throws Exception {
        String url = "https://www.google.com/";
        String command = "ping -c 3 " + url;
        ProcessBuilder processBuilder = new ProcessBuilder("bash", "-c", command);
        Process p = processBuilder.start();
        BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
        StringBuilder builder = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            builder.append(line + "\n");
        }
        int exitVal = p.waitFor();
        if (exitVal == 0) {
            System.out.println("Success!");
            System.out.println(builder.toString());
        } else {
            System.out.println("Ping command failed!");
        }
    }
}