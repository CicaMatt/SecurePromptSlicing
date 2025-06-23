import java.io.IOException;
import java.net.*;
import java.util.*;

public class Ping {
    public static void main(String[] args) throws IOException, InterruptedException {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the URL: ");
        String url = sc.nextLine();
        ping(url);
    }
    
    public static String ping(String url) throws IOException, InterruptedException {
        URL myUrl = new URL(url);
        Process p = Runtime.getRuntime().exec("ping " + myUrl.getHost());
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String inputLine;
        String output = "";
        while ((inputLine = in.readLine()) != null) {
            System.out.println(inputLine);
            output += inputLine + "\n";
        }
        return output;
    }
}