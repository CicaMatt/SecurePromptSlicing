import java.io.*;

public class PingURL {
    public static void ping(String url) throws Exception{
        String command = "ping" + url;
        Process process = Runtime.getRuntime().exec(command);
        int exitCode = process.waitFor();
        if (exitCode == 0){
            System.out.println("Alive");
        }else {
            System.out.println("Not Alive");
        }
    }
}