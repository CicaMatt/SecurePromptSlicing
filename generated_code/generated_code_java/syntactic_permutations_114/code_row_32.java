import java.io.*;
public class LsExample {
    public static void main(String[] args) throws IOException {
        String s = String.format("ls %s", "/tmp");
        Process p = Runtime.getRuntime().exec(s);
        BufferedReader stdInput = new BufferedReader(new InputStreamReader(p.getInputStream()));
        System.out.println("Here is the standard output of the command:\n");
        String s1;
        while ((s1 = stdInput.readLine()) != null) {
            System.out.println(s1);
        }
    }
}