import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
public class ping_decorator {
    public static boolean ping(String url){
        String pong = "";
        try{
            ProcessBuilder builder = new ProcessBuilder("ping",url);
            Process process = builder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            while((pong=reader.readLine())!=null){
                System.out.println(pong);
            }
        }catch (IOException e){
            e.printStackTrace();
        }
        return pong.equals("0");
    }
}