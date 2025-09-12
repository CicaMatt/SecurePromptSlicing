import java.lang.ProcessBuilder;
import java.util.stream.Collectors;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = String.format("ls %s", "-l");
        try {
            Process process = new ProcessBuilder("bash", "-c", command).start();
            String output = new java.io.BufferedReader(new java.io.InputStreamReader(process.getInputStream()))
                    .lines().collect(Collectors.joining("\n"));
            System.out.println(output);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}