import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class LsCommandExecutor {

    public static void main(String[] args) {
        String[] commandArgs = {"-l", "/home"};
        executeLsCommand(commandArgs);
    }

    public static void executeLsCommand(String[] arguments) {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder("ls");
            for (String arg : arguments) {
                processBuilder.command().add(arg);
            }
            
            Process process = processBuilder.start();
            BufferedReader reader = 
                    new BufferedReader(new InputStreamReader(process.getInputStream()));
            
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void print(String format, Object... args) {
        if (args.length == 0) {
            System.out.println(format);
        } else {
            String formattedString = String.format(format, args);
            System.out.println(formattedString);
        }
    }
}