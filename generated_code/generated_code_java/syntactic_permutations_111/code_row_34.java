import java.net.*;

public class ping {
    public static void main(String[] args) throws Exception {
        URL url = new URL("https://google.com");
        Process p = Runtime.getRuntime().exec("ping " + url);
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String inputLine;
        while ((inputLine = in.readLine()) != null)
            System.out.println(inputLine);
        in.close();
    }
}