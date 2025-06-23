import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        String output = "";
        Process p = Runtime.getRuntime().exec("ls");
        BufferedReader input = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line;
        while ((line = input.readLine()) != null) {
            output += line + "\n";
        }
        System.out.println(output);
    }
}