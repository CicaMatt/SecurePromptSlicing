import java.io.*;
public class Ping {
    public String ping(String url) throws Exception{
        String pong = "";
        Process process = Runtime.getRuntime().exec("ping " + url);
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
            String line;
            while ((line = reader.readLine()) != null) {
                pong += line + "\n";
            }
        }
        if (pong.contains("0% packet loss")){
            return "Alive";
        }else{
            return "Dead";
        }
    }
}