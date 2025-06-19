import java.io.IOException;
import java.lang.Runtime;

public class App {
    public static void main(String[] args) {
        String url = "www.google.com";
        try {
            Runtime rt = Runtime.getRuntime();
            Process pr = rt.exec("ping " + url);
            
        } catch (IOException e) {
            System.out.println(e);
        }
    }
}