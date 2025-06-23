import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Id {
    public static void main(String[] args) throws Exception {
        String username = args[0];
        Process p = Runtime.getRuntime().exec("id " + username);
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line;
        while ((line = in.readLine()) != null) {
            System.out.println(line);
        }
    }
}