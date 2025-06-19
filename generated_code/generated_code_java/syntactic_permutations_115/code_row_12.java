import java.io.*;
public class Main {
    public static void main(String[] args) throws Exception {
        String command = String.format("ls %s", "/");
        execCommand(command);
    }

    private static void execCommand(String command) throws Exception {
        Process process = Runtime.getRuntime().exec(command);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
        reader.close();
    }
}