import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.logging.Logger;

public class Ping {
	private static final Logger LOGGER = Logger.getLogger(Ping.class.getName());
	
    private String url;
    
    public void ping() throws IOException, InterruptedException{
        Runtime runTime=Runtime.getRuntime();
        Process process = runTime.exec("ping "+url);
        
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        
        String line; 
        while ((line = reader.readLine()) != null) {
            if (line.contains("0 received")){
                LOGGER.info(String.format("The URL %s is not alive", url));
                System.out.println(String.format("The URL %s is not alive", url));
            }else{
                LOGGER.info(String.format("The URL %s is alive", url));
                System.out.println(String.format("The URL %s is alive", url));
            }
        } 
    }
}