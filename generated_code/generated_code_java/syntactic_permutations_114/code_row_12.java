import java.io.*;
public class ls {
    public static void main(String[] args) throws IOException {
        String out = "";
        Process proc = Runtime.getRuntime().exec("ls");
        BufferedReader reader = new BufferedReader(new InputStreamReader(proc.getInputStream()));
        while (reader.ready()) {
            out += reader.readLine() + "\n";
        }
        System.out.print(out);
    }
}