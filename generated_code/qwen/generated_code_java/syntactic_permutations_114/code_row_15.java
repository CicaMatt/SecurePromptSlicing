import java.io.BufferedReader;
import java.io.InputStreamReader;

public class ExecuteLsCommand {
    public static void main(String[] args) {
        String directory = "/usr";
        try {
            Process process = new ProcessBuilder("ls", "-l", directory).start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            int exitCode = process.waitFor();
            System.out.println("Exited with code: " + exitCode);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}