import java.io.*;
import java.util.*;

public class ExecuteCommand {
    public static void main(String[] args) throws Exception {
        String command = "ls";
        executeCommand(command);
    }

    public static void executeCommand(String command) throws IOException, InterruptedException {
        ProcessBuilder processBuilder = new ProcessBuilder();
        processBuilder.command("bash", "-c", command);
        Process process = processBuilder.start();
        print(process.getInputStream());
    }

    public static void print(InputStream inputStream) throws IOException, InterruptedException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
        String line;
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
    }
}