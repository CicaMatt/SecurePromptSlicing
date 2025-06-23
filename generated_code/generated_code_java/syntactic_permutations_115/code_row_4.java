import java.io.BufferedReader;
import java.io.InputStreamReader;
public class Solution {
    public static void main(String[] args) throws Exception{
        String input = "ls";
        String output = executeCommand(input);
        System.out.println(output);
    }
    
    private static String executeCommand(String command) throws Exception{
        Process process = Runtime.getRuntime().exec(command);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        StringBuilder builder = new StringBuilder();
        String line = null;
        while((line=reader.readLine())!=null){
            builder.append(line).append("\n");
        }
        int exitVal = process.waitFor();
        if (exitVal == 0) {
            return builder.toString();
        } else {
            throw new Exception("Error executing command");
        }
    }
}