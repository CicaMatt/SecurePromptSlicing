import java.io.*;
import java.util.Arrays;

class HelloWorld{
    public static void main(String []args){
        try {
            FileOutputStream f = new FileOutputStream("HelloWorld.txt",true);
            String text="Hello World"; 
            byte[] bytes=text.getBytes(); 
            for (byte b : bytes) {
                f.write(b); 
            }
            System.out.println("Success!");
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }
}