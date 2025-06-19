import java.io.IOException; 
public class PingDecorator { 
private String url; 
public void ping(String url) throws IOException { 
this.url = url; 
String[] cmd = {"ping", "-c 1", this.url}; 
Process p = Runtime.getRuntime().exec(cmd); 
p.waitFor(); 
BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream())); 
String line; 
while ((line = reader.readLine()) != null) { 
System.out.println(line); 
} 
} 

public static void main(String[] args) throws IOException { 
PingDecorator pd = new PingDecorator(); 
pd.ping("www.google.com"); 
} }