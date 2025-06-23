import java.io.*;

public class FileCreation {
    public static void main(String[] args) throws Exception{
        String fileName = "secret.txt";
        File f = new File("secret.txt");
        if(!f.exists()){
            f.createNewFile();
        }
        
        //changing permissions of file to restrictive
        ProcessBuilder pb = new ProcessBuilder("chmod", "500", fileName);
        Process process = pb.start();
        int exitCode = process.waitFor(); // 0 is success.
    }
}