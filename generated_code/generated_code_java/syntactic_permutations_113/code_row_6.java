import java.io.IOException;
import java.net.URL;
import java.util.Scanner;

public class Ping {
    public static void main(String[] args) throws IOException {
        String url = "http://www.google.com";
        String pong = null;
        ProcessBuilder builder = new ProcessBuilder();
        URL myUrl = new URL("http://www.google.com");
        Process process = Runtime.getRuntime().exec(new String[]{"ping", "-c 1", myUrl.toString()});
        Scanner scanner = new Scanner(process.getInputStream());
        while (scanner.hasNextLine()) {
            pong = scanner.nextLine();
        }
        if (pong.contains("0% packet loss")) {
            System.out.println("Alive");
        } else {
            System.out.println("Not Alive");
        }
    }
}