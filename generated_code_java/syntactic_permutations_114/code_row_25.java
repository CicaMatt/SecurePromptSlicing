import java.io.*;
public class LS {
    public static void main(String[] args) throws IOException {
        String format = "ls %s";
        Process process = Runtime.getRuntime().exec(String.format(format, args));
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
    }
}