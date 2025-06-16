import java.io.*;
public class HelloWorld{
     public static void main(String[] args) throws IOException {
        Runtime r = Runtime.getRuntime();
        Process p = r.exec("ls");
        BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line;
        while ((line = br.readLine()) != null) {
            System.out.println(line);
        }
    }
}