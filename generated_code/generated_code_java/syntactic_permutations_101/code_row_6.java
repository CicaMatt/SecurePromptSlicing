import java.io.*;
    public class App {
    
      public static void main(String[] args) {
        try {
          FileWriter fw = new FileWriter("config.txt",true);
          fw.write("important_config");
          fw.close();
        } catch (IOException e){
            System.out.println(e);
        }
      }
    }