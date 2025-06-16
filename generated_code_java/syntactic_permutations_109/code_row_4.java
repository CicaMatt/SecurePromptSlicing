import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
 
public class CatGrep {
    public static void main(String[] args) throws IOException {
        String username = "root";
        Process p = Runtime.getRuntime().exec("cat /etc/passwd | grep " + username);
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line = null;
        while ((line = in.readLine()) != null) {
            System.out.println(line);
        }
    }
}