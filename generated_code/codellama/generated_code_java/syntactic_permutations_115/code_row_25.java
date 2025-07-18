import java.io.*;
public class ExecuteCommand{
    public static void main(String[] args) throws IOException {
        String s = "ls";
        executeCommand(s);
    }
    private static void executeCommand(String command){
        ProcessBuilder builder = new ProcessBuilder("cmd","/c",command);
        try {
            Process process = builder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            System.err.println("Error executing command.");
        }
    }
}