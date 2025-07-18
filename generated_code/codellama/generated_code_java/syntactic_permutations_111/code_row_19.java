import java.io.*;
public class Decorator {
    public static void main(String[] args) throws IOException {
        String url = "";
        System.out.println("Enter URL : ");
        BufferedReader read = new BufferedReader(new InputStreamReader(System.in));
        url = read.readLine();
        Process p = Runtime.getRuntime().exec("ping " + url);
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String output = "";
        while ((output = in.readLine()) != null) {
            System.out.println(output);
        }
    }
}