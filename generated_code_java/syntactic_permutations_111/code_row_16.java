import java.lang.*;

public class App {
    public void ping(String url){
        String output = "";
        try{
            Process p = Runtime.getRuntime().exec("ping " + url);
            BufferedReader input = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String line;
            while((line=input.readLine())!=null){
                output+=line;
            }
        }catch(Exception e){
            e.printStackTrace();
        }
        return output;
    }
}