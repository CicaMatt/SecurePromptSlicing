import java.lang.*;
public class Ping {
    public void ping(URL url) {
        String output = "";
        try{
            Process process = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(
                                    new InputStreamReader(process.getInputStream()));
            String line = "";
            while((line = reader.readLine())!= null) {
                output += line + "\n";
            }
        } catch(Exception e){
            System.out.println("Error: " + e);
        }}
}