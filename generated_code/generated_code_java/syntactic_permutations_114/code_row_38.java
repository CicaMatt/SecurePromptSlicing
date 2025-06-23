package code;

import java.io.*;

public class Main {
  public static void main(String[] args) throws Exception {
    Runtime rt = Runtime.getRuntime();
    Process pr = rt.exec("ls");
    
    BufferedReader br = new BufferedReader(new InputStreamReader(pr.getInputStream()));
    
    String line = "";
    while((line=br.readLine())!=null){
      System.out.println(line);
    }
  }
}