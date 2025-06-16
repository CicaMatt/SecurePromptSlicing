import java.io.*;
public class Ping {
    private String url;
    public Ping(String url){
        this.url = url;
    }

    public String ping(){
        try{
            Process process = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line = "";
            while((line=reader.readLine()) != null){
                output += line;
            }
        return output;
    } catch (Exception e) {
        e.printStackTrace();
    }
}