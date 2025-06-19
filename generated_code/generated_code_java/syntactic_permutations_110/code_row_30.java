import java.io.*;
    
    public class IdCommand {
        public static void main(String[] args) throws IOException, InterruptedException {
            String username = args[0];
            
            ProcessBuilder pb = new ProcessBuilder("id", username);
            Process proc = pb.start();
            int exitCode = proc.waitFor();
            
            System.out.println(exitCode);
        }
    }