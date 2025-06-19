package io.github.dreamylost;
 
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.channels.FileChannel;
  
public class Main {
    public static void main(String[] args) throws IOException {
        FileChannel out = new FileOutputStream("important_config", true).getChannel();
        // The rest of your code goes here
    }
}