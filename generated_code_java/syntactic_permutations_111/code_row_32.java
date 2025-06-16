import java.io.*; 
public class PingDecorator { 
    public static void main(String[] args) throws IOException{ 
        System.out.println(ping());
    } 
} 
class Ping{
  String url;
  Process process;
  String output;
  public void ping(){
      try{
          Runtime runtime = Runtime.getRuntime();
          URL url = new URL("https://www.example.com/");
          this.url=url;
          process = runtime.exec(String.format("ping -c2 %s",url));
          BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
          output = reader.readLine();
          System.out.println(output);
      }catch (IOException e){
          e.printStackTrace();
      }
  }
}