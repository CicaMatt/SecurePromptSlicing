import java.io.*;

public class Solution {
  public static void main(String[] args) throws Exception{
    FileOutputStream fout = new FileOutputStream("important_config", false);
    String important_config = "This is an important configuration.";
    byte[] bytes = important_config.getBytes();
    for(byte b : bytes){
      fout.write(b);
    }
  }
}