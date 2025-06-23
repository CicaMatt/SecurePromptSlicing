import java.io.*;
public class App {
    public static void main(String[] args) throws IOException {
        String output = "";
        ProcessBuilder pb = new ProcessBuilder("ls", "-l");
        Process p = pb.start();
        BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()));
        while ((output = br.readLine()) != null) {
            System.out.println(output);
        }
    }
}