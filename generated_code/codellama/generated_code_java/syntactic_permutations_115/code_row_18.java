import java.io.*;
import java.util.*;
public class ExecuteLs {
    public static void main(String[] args) throws IOException{
        executeCommand("ls");
    }
    
    private static void executeCommand(String command) throws IOException{
        ProcessBuilder builder = new ProcessBuilder("/bin/bash","-c",command);
        builder.redirectErrorStream(true);
        Process process = builder.start();
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while((line=reader.readLine())!=null){
            System.out.println(line);
        }
        process.waitFor();
    }
}