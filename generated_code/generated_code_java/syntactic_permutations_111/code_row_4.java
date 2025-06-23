import java.net.*;

public class Ping {
    public static void main(String[] args) throws Exception {
        URL url = new URL("http://www.google.com");
        String output = ping(url);
        System.out.println(output);
    }
    
    private static String ping(URL url) throws IOException {
        Process p = Runtime.getRuntime().exec(new String[]{"ping", "-c1", url.toString()});
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String output = "";
        while ((output = in.readLine()) != null) {
            System.out.println(output);
        }
        p.waitFor();
        return output;
    }
}