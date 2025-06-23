import java.io.*;
public class SystemCommand {
    public static void main(String[] args) throws IOException {
        String command = "ls";
        Process p1 = Runtime.getRuntime().exec(command);
        BufferedReader in = new BufferedReader(new InputStreamReader(p1.getInputStream()));
        String line;
        while((line = in.readLine()) != null)
            System.out.println(line);
    }
}