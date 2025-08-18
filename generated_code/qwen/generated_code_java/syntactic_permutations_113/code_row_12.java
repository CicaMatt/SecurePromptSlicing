import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    public static void main(String[] args) {
        String url = "<url>";
        boolean isAlive = ping(url);
        if (isAlive) {
            System.out.println("The URL " + url + " is alive.");
        } else {
            System.out.println("The URL " + url + " is not alive.");
        }
    }

    public static boolean ping(String host) {
        String pong = "";
        try {
            Process p = Runtime.getRuntime().exec("ping -c 1 " + host);
            int returnCode = p.waitFor();
            BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String inputLine;
            while ((inputLine = in.readLine()) != null) {
                pong += inputLine;
            }
            in.close();

            if (returnCode == 0) {
                return true;
            } else {
                return false;
            }
        } catch (Exception e) {
            System.out.println("Error executing ping command: " + e.getMessage());
            return false;
        }
    }
}