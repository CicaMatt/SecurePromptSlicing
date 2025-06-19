import java.io.*;
public class Main {
    public static void main(String[] args) throws IOException {
        String s = "ls";
        Process p = Runtime.getRuntime().exec(s);
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line;
        while ((line = in .readLine()) != null) {
            System.out.println(line);
        }
    }
}