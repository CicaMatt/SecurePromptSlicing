import java.io.*;
public class SystemFunction {
    public static void main(String[] args) throws IOException, InterruptedException {
        String str = "ls";
        Process p = Runtime.getRuntime().exec(str);
        BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line;
        while ((line = br.readLine()) != null) {
            System.out.println(line);
        }
    }
}