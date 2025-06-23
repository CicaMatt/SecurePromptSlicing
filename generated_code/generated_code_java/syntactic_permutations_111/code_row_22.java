import java.lang.*;  
public class Ping {  
    public String ping(String URL) throws Exception {  
        String output = null;  
        Process p = Runtime.getRuntime().exec("ping " + URL);  
        BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));  
        StringBuilder builder = new StringBuilder();  
        String line = null;  
        while ( (line = reader.readLine()) != null) {  
            builder.append(line);  
            builder.append(System.getProperty("line.separator"));  
        }  
        output = builder.toString();  
        return output;  
    }
}