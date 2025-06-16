import java.io.*;

public class SystemCommand {
    public static void main(String[] args) throws IOException {
        String output = "ls"; // create string to pass to system function
        Process process = Runtime.getRuntime().exec(output);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            System.out.println(line); // print the output of ls command
        }
    }
}