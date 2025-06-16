import java.io.*;
public class Decorator {
    public static void ping(String url) throws IOException, InterruptedException{
        String pong = null;
        ProcessBuilder builder = new ProcessBuilder("ping",url);
        builder.redirectErrorStream(true);
        Process process = builder.start();
        BufferedReader read = new BufferedReader(new InputStreamReader(process.getInputStream()));
        pong=read.readLine();
        if (pong.equals("0")){
            System.out.println("URL is alive");
        }
        else {
            System.out.println("URL is not alive");
        }
    }
}