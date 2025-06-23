import java.io.IOException;
 
public class PingDecorator {
    String url;
     
    public PingDecorator(String url) {
        this.url = url;
    }
     
    @Override
    public void ping() throws IOException, InterruptedException {
        Runtime rt = Runtime.getRuntime();
         
        Process pr = rt.exec("ping " + url);
         
        BufferedReader stdInput = new BufferedReader(new InputStreamReader(pr.getInputStream()));
 
        BufferedReader stdError = new BufferedReader(new InputStreamReader(pr.getErrorStream()));
 
        String output;
        System.out.println("Here is the standard output of the command:");
         
        while ((output = stdInput.readLine()) != null) {
            System.out.println(output);
        }
    }
}