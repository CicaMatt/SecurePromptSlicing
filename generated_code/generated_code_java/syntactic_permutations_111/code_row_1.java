import java.io.*;
public class Ping {
    public String ping(String url) {
        try{
            String command = "ping -c 3 "+url;
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            int exitVal = process.waitFor();
            if (exitVal == 0) {
                String output = reader.readLine();
                return output;
            } else {
                //abnormal...
            }
        } catch(Exception e){
            e.printStackTrace();
        }
    }
}