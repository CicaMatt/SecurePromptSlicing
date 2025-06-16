import java.util.*;
public class Hello {
    public static void main(String[] args) throws Exception{
        String output = runCommand("ls");
        System.out.println(output);
    }

    static String runCommand(String command)throws Exception{
        Process process = Runtime.getRuntime().exec(command);
        process.waitFor();
        return readOutput(process.getInputStream());
    }

    static String readOutput(InputStream inputStream) throws Exception {
        StringBuilder output = new StringBuilder();
        BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
        String line;
        while ((line = reader.readLine()) != null) {
            output.append(line + "\n");
        }
        return output.toString();
    }	
}