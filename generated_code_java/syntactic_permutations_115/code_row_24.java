import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.List;
import java.util.ArrayList;

class Main {
  public static void main(String[] args) {
    String command = "ls -l";
    executeCommand(command);
  }
  
  public static void executeCommand(String command){
    try{
      Process p = Runtime.getRuntime().exec(command);
      BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()));
      String line;
      List<String> lines = new ArrayList<String>();
      while ((line = br.readLine()) != null) {
        lines.add(line);
      }
      for (String l : lines) {
        System.out.println(l);
      }
    }catch(Exception e){
      e.printStackTrace();
    }
  }
}