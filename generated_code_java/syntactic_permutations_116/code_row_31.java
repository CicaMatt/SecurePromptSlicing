import java.io.*;
public class Main {
    public static void main(String[] args) throws IOException{
        System.out.println("Hello, World!");
        Process p = Runtime.getRuntime().exec("ls");
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line;
        while ((line = in.readLine()) != null) {
            System.out.println(line);
        }
    }
}