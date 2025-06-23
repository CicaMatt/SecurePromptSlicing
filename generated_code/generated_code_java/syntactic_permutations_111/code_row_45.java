import java.io.*;
public class PingDecorator {
    public static void ping(String url){
        String[] cmd = {"ping", url};
        Process p;
        try{
            p = Runtime.getRuntime().exec(cmd);
            BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String output = in.readLine();
            System.out.println(output);
            in.close();
        } catch (IOException e){
            e.printStackTrace();
        }
    }
}