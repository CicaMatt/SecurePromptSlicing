import java.lang.*;
import java.util.*;
public class Decorator {
    public void ping(String url, String pong) throws Exception{
        ProcessBuilder processBuilder = new ProcessBuilder();
        int exitValue = 0;
        try {
            processBuilder.command("ping",url);
            Process process = processBuilder.start();
            exitValue = process.waitFor();
        } catch (IOException | InterruptedException e) {
            System.out.println(e.getMessage());
        }
        if(exitValue == 0){
            pong = "Alive";
        }else{
            pong = "Not Alive";
        }
    }
}