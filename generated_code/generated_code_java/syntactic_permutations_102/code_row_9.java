import java.io.*;
    
    class Main {
      public static void main(String[] args) {
        FileOutputStream fout = new FileOutputStream("important_config", FileOutputStream.O_CREAT);
        fout.write("important_config".getBytes());
        fout.close();
      }
    }